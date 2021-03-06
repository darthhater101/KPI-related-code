#include "scanner.h"

int main()
{
	printf("Creating db..\n\n");
	create_db("scanner.csv", "scanner.db");

	printf("Print db:\n\n");
	print_db("scanner.db");
	printf("\n");

	printf("Reindexing db..\n\n");
	reindex("scanner.db");
	printf("\n");

	printf("Adding \"Asus;AS1055;2009;99.99;210;297\" :\n");
	add_scanner("scanner.db", "Asus;AS1055;2009;99.99;210;297");

	printf("Print db:\n\n");
	print_db("scanner.db");
	printf("\n");

	printf("Deleting id = 5:\n\n");
	del_scanner("scanner.db", 5);

	printf("Print db:\n\n");
	print_db("scanner.db");

	printf("Selecting record by value and field..\n\n");
	RECORD_SET* rs = select_db("scanner.db", "manufacturer", "Asus");

	printf("Print rs:\n");
	print_rec_set(rs);
	printf("\n");

	printf("Selecting records indexes..\n\n");
	rs = get_recs_by_index("scanner.db", (char*)"manufacturer");

	printf("Print rs:\n");
	print_rec_set(rs);
	return 0;
}