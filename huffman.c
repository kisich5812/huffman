#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "huffman.h"

struct symbol* dif_sym(FILE* file, symbol* alph, int *val_syms)
{
	int c = fgetc(file);
	while(c != EOF)
	{
		bool find_sym = 0;	      //задали переменную поиска в массиве структур 0

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
		if (!find_sym && alph[*val_syms].sym == 0)
		{
			alph[*val_syms].sym = c;
			alph[*val_syms].val++;
			(*val_syms)++;
		}

		c = fgetc(file);
	}
	return alph;
}

void sort(struct symbol* a, int n)
{
	int i = n;
	long long minimum = LLONG_MAX;
	int num_min = -1;
	while(i>0)
	{
		for(int j = n-i; j<n; j++)
		{
			if (a[j].val < minimum)
			{
				minimum = a[j].val;
				num_min = j;
			}
		}
		int change_sym = a[n-i].sym;
		long long change_val = a[n-i].val;
		a[n-i].sym = a[num_min].sym;
		a[n-i].val = a[num_min].val;
		a[num_min].sym = change_sym;
		a[num_min].val = change_val;
		minimum = LLONG_MAX;
		i--;
	}
}
