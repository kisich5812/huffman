#include <stdio.h>
#include <stdlib.h>
#include "main.h"

int main(int argc, char* argv[])
{
	if (argc != 2)
		return -fprintf(stderr, "Usage: <file>\n");
	FILE* finput = fopen(argv[1], "r");
	if (!finput)
		return -fprintf(stderr, "Error open file\n");
	
	int val_sym = 1; 
	struct symbol* alph = (symbol*) calloc((size_t)val_sym, sizeof(symbol));
	
	alph = dif_sym(finput, alph, &val_sym);
	
	printf("количество символов: %d\n", val_sym);
	printf("sym val\n");
	for(int i = 0; i<val_sym; i++)
		printf("'%c'  %lld \n", alph[i].sym, alph[i].val); 

	free(alph);
	fclose(finput);
	return 0;
}
