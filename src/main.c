#include <stdio.h>
#include <stdlib.h>
#include "main.h"

int main(int argc, char* argv[])
{
	FILE* finput = open_file(argc, argv);
	if (finput == NULL)
		return -1;

	int val_sym = 0; 
	struct symbol* alph = (struct symbol*) calloc(256, sizeof(struct symbol));
	
	alph = dif_sym(finput, alph, &val_sym);
	
	//print_symbols(alph, val_sym);
	struct symbol* table = make_table(alph, val_sym);

	//print_t(table);
	codes(table, NULL, -1);
	print_codes(table);

	destroy_table(table);
	free(alph);
	fclose(finput);
	
	return 0;
}
