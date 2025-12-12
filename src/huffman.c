#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include "huffman.h"

struct symbol* dif_sym(FILE* file, struct symbol* alph, int *val_syms)
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
	long long maximum = -1;
	int num_min = -1;
	while(i>0)
	{
		for(int j = n-i; j<n; j++)
		{
			if (a[j].val > maximum)
			{
				maximum = a[j].val;
				num_min = j;
			}
		}
		int change_sym = a[n-i].sym;
		long long change_val = a[n-i].val;
		struct symbol* c_left = a[n-i].left;
		struct symbol* c_right = a[n-i].right;
		a[n-i].sym = a[num_min].sym;
		a[n-i].val = a[num_min].val;
		a[n-i].left = a[num_min].left;
		a[n-i].right = a[num_min].right;
		a[num_min].sym = change_sym;
		a[num_min].val = change_val;
		a[num_min].left = c_left;
		a[num_min].right = c_right;
		maximum = -1;
		i--;
	}
}

struct symbol* make_copy(struct symbol alph)
{
	struct symbol* c = (struct symbol*) calloc(1, sizeof(struct symbol));
	*c = alph;
	return c;
}


struct symbol* make_table(struct symbol* alph, int val_sym)
{
	struct symbol* root = NULL;
	if (val_sym > 2)
	{
		sort(alph, val_sym);
		struct symbol* c1 = make_copy(alph[val_sym-1]);
		struct symbol* c2 = make_copy(alph[val_sym-2]);
		alph[val_sym-2].sym = '\0';
		alph[val_sym-2].val = alph[val_sym-1].val + alph[val_sym-2].val;
		alph[val_sym-2].right = c1;
		alph[val_sym-2].left = c2;
		root = make_table(alph, val_sym-1);
	}
	if (val_sym == 2)
	{
		root = (struct symbol*) calloc(1, sizeof(struct symbol));
		root->sym = '\0';
		root->val = 0;
		struct symbol* c1 = make_copy(alph[val_sym-1]);
		struct symbol* c2 = make_copy(alph[val_sym-2]);
		root->right = c1;
		root->left = c2;
	}
	if (val_sym == 1)
	{
		root = (struct symbol*) calloc(1, sizeof(struct symbol));
		root->sym = '\0';
		root->val = 0;
		root->right = alph;
		root->left = NULL;
	}
	else if (val_sym == 0)
		return 0;
	return root;
}

void destroy_table(struct symbol* table)
{
	if (!table)
		return;
	destroy_table(table->left);
	destroy_table(table->right);
	free(table);
}

int codes(struct symbol* t, struct symbol* t_old, int c) {
	if (!t)
		return 0;
	if (t_old) {
		//printf("t: %p, t_old: %p\nt->code: %p, t_old->code: %p\n", t, t_old, t->code, t_old->code);
		strcat(t->code, t_old->code);
		if(c)
			strcat(t->code, "1");
		else
			strcat(t->code, "0");
	}
	codes(t->left, t, 0);
	codes(t->right, t, 1);
	return 0;
}
