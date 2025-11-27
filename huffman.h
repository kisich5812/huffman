#ifndef _HUFFMAN_H_
#define _HUFFMAN_H_

#include "typcon.h"
struct symbol* dif_sym(FILE* file, symbol* alph, int *val_syms);
void sort(struct symbol* a, int n);

#endif
