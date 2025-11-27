#include <stdio.h>
#include "io_func.h"

FILE* open_file(int argc, char* argv[])
{
	if (argc != 2)
	{
                fprintf(stderr, "Usage: <file>\n");
		return NULL;
	}
	FILE* finput = fopen(argv[1], "r");
        if (!finput)
	{
		fprintf(stderr, "Error open file\n");
		return NULL;
	}
	return finput;
}

int print_symbols(struct symbol* alph, int val_sym)
{
	printf("количество символов: %d\n", val_sym);
        printf("sym val\n");
        for(int i = 0; i<val_sym; i++)
                printf("'%c'  %lld \n", alph[i].sym, alph[i].val);
	return 0;
}

int print_table(struct symbol* table, int h)
{
	h++;
	printf("table:\n");
	if ((table->left))
	{
		printf("h: %d val: %c %lld\n", h, table->left->sym, table->left->val);
		print_table(table->left, h);
	}
	if ((table->right))
	{
		printf("h: %d val: %c %lld\n", h, table->right->sym, table->right->val);
		print_table(table->right, h);
	}
		//printf("h: %d\nval: '%c' %lld\n", h, table->sym, table->val);
	return 0;
}
