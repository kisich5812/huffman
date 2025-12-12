#ifndef _HUFFMAN_H_
#define _HUFFMAN_H_

#include "typcon.h"

struct symbol* dif_sym(FILE* file, symbol* alph, int *val_syms);
void sort(struct symbol* a, int n);
struct symbol* make_table(struct symbol* alph, int val_sym);
void destroy_table(struct symbol* table);
int codes(struct symbol* table, int is_left);

#endif
