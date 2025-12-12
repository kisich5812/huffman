#ifndef _ENC_H_
#define _ENC_H_

#include "huffman.h"
#include "typcon.h"
#include "io_func.h"

int main_enc(Flags* f);
int main_dec(Flags* f);
int check_code(char* a, char* b, int n);

#endif
