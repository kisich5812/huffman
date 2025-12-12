#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "flags.h"

Flags* check_flags(int argc, char* argv[]) {
	Flags* f = (Flags*) calloc(1, sizeof(Flags));
	if (!f) return NULL;
	_Bool exit = 0;
	for (int i = 1; i<argc; i++) {
		if (strcmp(argv[i], "-o") == 0) {
			if(i+1<argc)
			{
				i++;
				f->output_file = argv[i];
			}
			else {
				printf("Имя файла не задано!\n");
				exit = 1;
			}
		}
		else if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
			print_help();
			exit = 1;
		}
		else if (strcmp(argv[i], "--screen") == 0)
			f->screen = 1;
		else if (strcmp(argv[i], "-i") == 0) {
			if(i+1<argc)
			{
				i++;
				f->input_file = argv[i];
			}
			else {
				printf("Имя файла не задано!\n");
				exit = 1;
			}
		}
		else if (strcmp(argv[i], "-e") == 0 || strcmp(argv[i], "--enc") == 0)
			f->enc = 1;
		else if (strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "--dec") == 0)
			f->dec = 1;
		else if (strcmp(argv[i], "-t") == 0) {
			if(i+1<argc)
			{
				i++;
				f->table_file = argv[i];
			}
			else {
				printf("Имя файла не задано!\n");
				exit = 1;
			}
		}
		else {
			printf("Unknown argument: %s\n", argv[i]);
			exit = 1;
		}
		if (exit) break;
	}
	if (!exit && !f->input_file)
	{
		exit = 1;
		printf("Не задано имя входного файла!\n");\
	}
	if (exit) return NULL;
	else return f;
}
