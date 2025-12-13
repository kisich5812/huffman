#ifndef _TYPCON_
#define _TYPCON_

#include <stdbool.h>

struct symbol {
	int sym;
	long long val;
	struct symbol* left;
	struct symbol* right;
	char code[1000];
};

typedef struct code {
	int sym;
	char code[1000];
} Code;

typedef struct flags {
	char* output_file;
	char* table_file;
	bool screen;
	char* input_file;
	bool enc;
	bool dec;
} Flags;

#endif
