#pragma once
#pragma warning (disable : 4996)
#pragma warning (disable : 4244)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
	int id;
	char manufacturer[127];
	int year;
	char model[127];
	float price;
	int x_size;
	int y_size;
} SCAN_INFO;

typedef struct
{
	int rec_nmb;
	SCAN_INFO *recs;
} RECORD_SET;

void create_db(const char* csv, const char *db);
int number_of_lines(FILE *f);
SCAN_INFO get_scan(char *str);
void get_str(SCAN_INFO* t, char* tmp);
void reindex(const char *db);
void del_scanner(const char *db, int id);
void add_scanner(const char *db, const char* scanner_str);
RECORD_SET* select_db(const char *db, const char *field, const char *value);
void print_rec_set(RECORD_SET *rs);
RECORD_SET* get_recs_by_index(const char* db, char* field);
int make_index(const char *db, const char *field_name);
void print_db(const char *db);
