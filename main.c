#include <stdio.h>
#include <stdlib.h>

struct symbol
{
	int sym;
	long long val;
};

struct symbol* dif_sym(FILE* file, symbol* alph, int *val_syms);

struct symbol* dif_sym(FILE* file, symbol* alph, int *val_syms)
{
	int c = fgetc(file);
	while(c != EOF)
	{
		bool find_sym = 0;		//задали переменную поиска в массиве структур 0
		
		for (int i = 0; i<*val_syms; i++) // побежали искать
		{
			if(alph[i].sym == c)
			{
				alph[i].val++;
				find_sym = !find_sym;
				break;
			}
		}
		// если не нашли
		if (!find_sym && alph[*val_syms-1].sym == 0)
		{
			alph[*val_syms-1].sym = c;
			alph[*val_syms-1].val++;
			find_sym = !find_sym;
		}

		if (!find_sym && alph[*val_syms-1].sym != 0)
		{
			alph = (struct symbol*) realloc(alph, ((size_t) *val_syms+1) * sizeof(symbol));
			(*val_syms)++;
			alph[*val_syms-1].sym = c;
			alph[*val_syms-1].val = 1;
			find_sym = !find_sym;
		}

		c = fgetc(file);
	}
	return alph;
}

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
