#include <stdio.h>
#include <stdlib.h>
#include "main.h"

int main(int argc, char* argv[])
{
	FILE* finput = open_file(argc, argv);
	if (finput == NULL)
		return -1;

	int val_sym = 0; 
	struct symbol* alph = (symbol*) calloc(256, sizeof(symbol));
	
	alph = dif_sym(finput, alph, &val_sym);
	
	print_symbols(alph, val_sym);
	//sort(alph, val_sym);
	struct symbol* table = make_table(alph, val_sym);

	//print_table(table, 0);
	print_t(table);
	codes(table, -1);

	destroy_table(table);
	free(alph);
	fclose(finput);
	
	printf("The end!");
	return 0;
}
