#ifndef _IO_FUNC_
#define _IO_FUNC_

#include "typcon.h"

FILE* open_file(int argc, char* argv[]);
int print_symbols(struct symbol* alph, int val_sym);
int print_table(struct symbol* table, int h);
void print_t(struct symbol* tree);
int print_codes(struct symbol* table);

#endif
