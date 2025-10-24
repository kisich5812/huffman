#include <stdio.h>
#include <stdlib.h>
#include "main.h"

int main(int argc, char* argv[])
{
	FILE* finput = open_file(argc, argv);
	if (finput == NULL)
		return -1;

	int val_sym = 1; 
	struct symbol* alph = (symbol*) calloc((size_t)val_sym, sizeof(symbol));
	
	alph = dif_sym(finput, alph, &val_sym);
	
	print_symbols(alph, val_sym);

	free(alph);
	fclose(finput);
	return 0;
}
