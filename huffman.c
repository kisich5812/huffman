#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"

struct symbol* dif_sym(FILE* file, symbol* alph, int *val_syms)
{
        int c = fgetc(file);
        while(c != EOF)
        {
                bool find_sym = 0;              //задали переменную поиска в массиве структур 0

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
