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
	
	sort(alph, val_sym);
	print_symbols(alph, val_sym);

	free(alph);
	fclose(finput);
	return 0;
}
