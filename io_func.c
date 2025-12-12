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

/*int print_table(struct symbol* table, int h)
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
}*/

int _print_t(struct symbol *tree, int is_left, int offset, int depth, char s[20][255])
{
    char b[20];
    int width = 6;

    if (!tree) return 0;

    if (is_left)
	    sprintf(b, "(%03d)0", tree->sym);
    else
	    sprintf(b, "(%03d)1", tree->sym);


    int left  = _print_t(tree->left,  1, offset,                depth + 1, s);
    int right = _print_t(tree->right, 0, offset + left + width, depth + 1, s);

#ifdef COMPACT
    for (int i = 0; i < width; i++)
        s[depth][offset + left + i] = b[i];

    if (depth && is_left) {

        for (int i = 0; i < width + right; i++)
            s[depth - 1][offset + left + width/2 + i] = '-';

        s[depth - 1][offset + left + width/2] = '.';

    } else if (depth && !is_left) {

        for (int i = 0; i < left + width; i++)
            s[depth - 1][offset - width/2 + i] = '-';

        s[depth - 1][offset + left + width/2] = '.';
    }
#else
    for (int i = 0; i < width; i++)
        s[2 * depth][offset + left + i] = b[i];

    if (depth && is_left) {

        for (int i = 0; i < width + right; i++)
            s[2 * depth - 1][offset + left + width/2 + i] = '-';

        s[2 * depth - 1][offset + left + width/2] = '+';
        s[2 * depth - 1][offset + left + width + right + width/2] = '+';

    } else if (depth && !is_left) {

        for (int i = 0; i < left + width; i++)
            s[2 * depth - 1][offset - width/2 + i] = '-';

        s[2 * depth - 1][offset + left + width/2] = '+';
        s[2 * depth - 1][offset - width/2 - 1] = '+';
    }
#endif

    return left + width + right;
}

void print_t(struct symbol *tree)
{
    char s[20][255];
    for (int i = 0; i < 20; i++)
        sprintf(s[i], "%80s", " ");

    _print_t(tree, 0, 0, 0, s);

    for (int i = 0; i < 20; i++)
        printf("%s\n", s[i]);
}
