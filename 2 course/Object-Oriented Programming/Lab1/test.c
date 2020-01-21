#include "argz.h"
#include "conio.h"


int main()
{
	char *argz;
	size_t argz_lenth;
	char *const string = (char *const)"SHELL=/bin/bash:usr=monty:PWD=/bin/monty:LANG=en_US.UTF-8";

	printf("String: %s\n\n", string);

	printf("Argz_create_sep test: \n");
	argz_create_sep(string, 58, &argz, &argz_lenth);
	printf("Argz_len = %d\n", argz_lenth + 1);
	printf("Vector : \n");
	argz_print(argz, argz_lenth);
	printf("\n\n");

	printf("Argz_count test: \n");
	printf("\tArgz_count = %d", argz_count(argz, argz_lenth));
	printf("\n\n");

	printf("Argz_add test: \n");
	printf("Adding \"creator=Darth:BIN/C++\":\n");
	argz_add(&argz, &argz_lenth, "creator=Darth:BIN/C++");
	argz_print(argz, argz_lenth);
	printf("\n\n");

	printf("Argz_delete test: \n");
	printf("Delete \"usr=monty\":\n");
	argz_delete(&argz, &argz_lenth, (char*)"usr=monty");
	argz_print(argz, argz_lenth);
	printf("\n\n");

	printf("Argz_insert test: \n");
	printf("Insert Ruby before Darth:\n");
	argz_insert(&argz, &argz_lenth, (char*)"Darth", "Ruby ");
	argz_print(argz, argz_lenth);
	printf("\n\n");


	printf("Argz_replace test:\n");
	printf("Replace string LANG=en_US.UTF-8 to LANG=fr:\n");
	argz_replace(&argz, &argz_lenth, "LANG=en_US.UTF-8", "LANG=fr");
	argz_print(argz, argz_lenth);
	printf("\n\n");

	printf("Argz_print test:\n");
	argz_print(argz, argz_lenth);
	printf("\n\n");

	printf("Argz_next test:\n");
	char* entry = NULL;
	entry = argz_next(argz, argz_lenth, entry);
	while (entry)
	{
		printf("\t%s\n", entry);
		entry = argz_next(argz, argz_lenth, entry);
	}

	_getch();
	return 0;
}
