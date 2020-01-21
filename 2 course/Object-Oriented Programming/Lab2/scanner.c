#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "scanner.h"

SCAN_INFO get_scan(char* str) 
{
	SCAN_INFO scan;
	char* tmp = (char*)malloc(sizeof(char)*strlen(str) + 1);
	strcpy(tmp, str);

	char* entry = strtok(tmp, ";");
	strcpy(scan.manufacturer, entry);

	entry = strtok(0, ";");
	strcpy(scan.model, entry);

	entry = strtok(0, ";");
	scan.year = atoi(entry);

	entry = strtok(0, ";");
	scan.price = atof(entry);

	entry = strtok(0, ";");
	scan.x_size = atoi(entry);

	entry = strtok(0, ";");
	scan.y_size = atoi(entry);

	free(tmp);
	return scan;
}

void get_str(SCAN_INFO* scan, char* tmp) 
{
	sprintf(tmp, "%s;%s;%d;%f;%d;%d;%d", scan->manufacturer, scan->model, scan->year, scan->price, scan->x_size, scan->y_size, scan->id);
}

int number_of_lines(FILE* csv_file) 
{
	int lines = 0;
	char c = 0;
	while (c != EOF)
	{
		c = fgetc(csv_file);
		if (c == '\n') lines++;
	}
	rewind(csv_file);
	return lines+1;
}

void create_db(const char* csv, const char *db) 
{
	FILE* csv_file = fopen(csv, "r");
	FILE* db_file = fopen(db, "wb");
	int lines = number_of_lines(csv_file);
	fwrite(&lines, sizeof(int), 1, db_file);

	for (int i = 0; i < lines; i++) {
		char tmp[256];
		fscanf(csv_file, "%[^\n]\n", tmp);
		SCAN_INFO scan = get_scan(tmp);
		scan.id = i;
		fwrite(&scan, sizeof(SCAN_INFO), 1, db_file);
	}
	fclose(csv_file);
	fclose(db_file);
}

int make_index(const char *db, const char *field_name) 
{
	FILE* db_file = fopen(db, "rb");

	char idx[30];
	strcpy(idx, field_name);
	strcat(idx, ".idx");

	FILE* idx_file = fopen(idx, "w");

	if (db_file == 0 || idx_file == 0) {
		return 0;
	}

	int tmp;
	SCAN_INFO* structs;
	fread(&tmp, sizeof tmp, 1, db_file);
	structs = (SCAN_INFO*)malloc(sizeof(SCAN_INFO)*tmp);
	fread(structs, sizeof(SCAN_INFO), tmp, db_file);
	fclose(db_file);


	for (int i = 0; i < tmp; i++) 
	{
		for (int j = 0; j < tmp - 1; j++) 
		{
			int flag = 0;
			if (strcmp(field_name, "id") == 0) 
			{
				if (structs[j].id > structs[j + 1].id) flag = 1;
			}
			if (strcmp(field_name, "year") == 0) 
			{
				if (structs[j].year > structs[j + 1].year) flag = 1;
			}
			if (strcmp(field_name, "price") == 0) 
			{
				if (structs[j].price > structs[j + 1].price) flag = 1;
			}
			if (strcmp(field_name, "x_size") == 0) 
			{
				if (structs[j].x_size > structs[j + 1].x_size) flag = 1;
			}
			if (strcmp(field_name, "y_size") == 0) 
			{
				if (structs[j].y_size > structs[j + 1].y_size) flag = 1;
			}
			if (strcmp(field_name, "model") == 0) 
			{
				flag = strcmp(structs[j].model, structs[j + 1].model);
			}
			if (strcmp(field_name, "manufacturer") == 0) 
			{
				flag = strcmp(structs[j].manufacturer, structs[j + 1].manufacturer);
			}

			if (flag > 0) 
			{
				SCAN_INFO scan = structs[j];
				structs[j] = structs[j + 1];
				structs[j + 1] = scan;
			}
		}
	}
	for (int i = 0; i < tmp; i++) 
	{
		fprintf(idx_file, "%d ", structs[i].id);
	}
	fclose(idx_file);
	return 1;
}

void print_db(const char *db) 
{
	FILE*  db_file = fopen(db, "rb");
	RECORD_SET* res = (RECORD_SET*)malloc(sizeof(RECORD_SET));
	fread(&(res->rec_nmb), sizeof(int), 1, db_file);
	res->recs = (SCAN_INFO*)malloc(sizeof(SCAN_INFO)*res->rec_nmb);
	fread(res->recs, sizeof(SCAN_INFO), res->rec_nmb, db_file);

	for (int i = 0; i < res->rec_nmb; i++) {
		char tmp[255];
		get_str(&(res->recs[i]), tmp);
		printf("%s\n", tmp);
	}
}

void reindex(const char *db) 
{
	make_index(db, "id");
	make_index(db, "manufacturer");
	make_index(db, "year");
	make_index(db, "model");
	make_index(db, "price");
	make_index(db, "y_size");
	make_index(db, "x_size");
}

void del_scanner(const char *db, int id) 
{
	FILE* db_file = fopen(db, "rb");
	
	RECORD_SET* res = (RECORD_SET*)malloc(sizeof(RECORD_SET));
	fread(&(res->rec_nmb), sizeof(int), 1, db_file);
	res->recs = (SCAN_INFO*)malloc(sizeof(SCAN_INFO)*res->rec_nmb);
	fread(res->recs, sizeof(SCAN_INFO), res->rec_nmb, db_file);

	fclose(db_file);

	if(id > res->rec_nmb - 1 || id < 0)
	{
		printf("No match found by id\n");
		return;
	}

	FILE* db_file_out = fopen(db, "wb");
	res->rec_nmb--;
	fwrite(&(res->rec_nmb), sizeof(int), 1, db_file_out);

	for (int i = 0; i < res->rec_nmb + 1; i++) 
	{
		if (res->recs[i].id != id) 
		{
			fwrite(res->recs + i, sizeof(SCAN_INFO), 1, db_file_out);
		}
	}

	fclose(db_file_out);
	free(res->recs);
	free(res);
	reindex(db);
}

void add_scanner(const char *db, const char* scanner_str) 
{
	FILE* db_file = fopen(db, "rb");

	RECORD_SET* res = (RECORD_SET*)malloc(sizeof(RECORD_SET));
	fread(&(res->rec_nmb), sizeof(int), 1, db_file);
	res->recs = (SCAN_INFO*)malloc(sizeof(SCAN_INFO)*res->rec_nmb);
	fread(res->recs, sizeof(SCAN_INFO), res->rec_nmb, db_file);

	fclose(db_file);

	FILE* db_file_out = fopen(db, "wb");
	res->rec_nmb++;
	fwrite(&(res->rec_nmb), sizeof(int), 1, db_file_out);
	fwrite(res->recs, sizeof(SCAN_INFO), res->rec_nmb - 1, db_file_out);

	int max_id = -1;
	for (int i = 0; i < res->rec_nmb - 1; i++) {
		if (res->recs[i].id > max_id) max_id = res->recs[i].id;
	}
	SCAN_INFO scan = get_scan((char*)scanner_str);
	scan.id = max_id + 1;
	fwrite(&scan, sizeof(SCAN_INFO), 1, db_file_out);

	fclose(db_file_out);
	free(res->recs);
	free(res);
	reindex(db);

}

RECORD_SET* select_db(const char *db, const char *field, const char *value)
{
	FILE* db_file = fopen(db, "rb");

	int tmp;
	SCAN_INFO* structs;
	fread(&tmp, sizeof tmp, 1, db_file);
	structs = (SCAN_INFO*)malloc(sizeof(SCAN_INFO)*tmp);
	fread(structs, sizeof(SCAN_INFO), tmp, db_file);
	fclose(db_file);

	RECORD_SET* rec_struct = (RECORD_SET*)malloc(sizeof(RECORD_SET));
	rec_struct->recs = (SCAN_INFO*)malloc(sizeof(SCAN_INFO)*tmp);

	int records_num = 0;
	for (int i = 0; i < tmp; i++) 
	{
		int flag_num = 0;
		int flag_str = -1;
		if (strcmp(field, "id") == 0) 
		{
			if (structs[i].id == atoi(value)) flag_num = 1;
		}
		if (strcmp(field, "year") == 0) 
		{
			if (structs[i].year == atoi(value)) flag_num = 1;
		}
		if (strcmp(field, "price") == 0) 
		{
			if (structs[i].price == atof(value)) flag_num = 1;
		}
		if (strcmp(field, "x_size") == 0) 
		{
			if (structs[i].x_size == atoi(value)) flag_num = 1;
		}
		if (strcmp(field, "y_size") == 0) 
		{
			if (structs[i].y_size == atoi(value)) flag_num = 1;
		}
		if (strcmp(field, "model") == 0) 
		{
			flag_str = strcmp(structs[i].model, value);
		}
		if (strcmp(field, "manufacturer") == 0) 
		{
			flag_str = strcmp(structs[i].manufacturer, value);
		}
		if (flag_num == 1 || flag_str == 0) 
		{
			rec_struct->recs[records_num] = structs[i];
			records_num++;
		}
	}
	rec_struct->rec_nmb = records_num;
	return rec_struct;
}

void print_rec_set(RECORD_SET *rs) 
{
	for (int i = 0; i < rs->rec_nmb; i++) 
	{
		char tmp[255];
		get_str(rs->recs + i, tmp);
		printf("%s\n", tmp);
	}
}

RECORD_SET* get_recs_by_index(const char* db, char* field) 
{
	FILE* db_file = fopen(db, "rb");

	RECORD_SET* res1 = (RECORD_SET*)malloc(sizeof(RECORD_SET));
	fread(&(res1->rec_nmb), sizeof(int), 1, db_file);
	res1->recs = (SCAN_INFO*)malloc(sizeof(SCAN_INFO)*res1->rec_nmb);
	fread(res1->recs, sizeof(SCAN_INFO), res1->rec_nmb, db_file);

	fclose(db_file);

	char tmp[30];
	strcpy(tmp, field);
	strcat(tmp, ".idx");

	RECORD_SET* res2 = (RECORD_SET*)malloc(sizeof(RECORD_SET));
	res2->rec_nmb = res1->rec_nmb;
	res2->recs = (SCAN_INFO*)malloc(sizeof(SCAN_INFO)*res1->rec_nmb);

	FILE* idx_file = fopen(tmp, "r");
	for (int i = 0; i < res1->rec_nmb; i++) {
		int x;
		fscanf(idx_file, "%d", &x);
		for (int j = 0; j < res1->rec_nmb; j++) {
			if (res1->recs[j].id == x) {
				res2->recs[i] = res1->recs[j];
				break;
			}
		}
	}
	fclose(idx_file);
	free(res1->recs);
	free(res1);
	return res2;
}
