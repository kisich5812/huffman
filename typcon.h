#ifndef _TYPCON_
#define _TYPCON_

#include "typcon.h"

struct symbol {
	int sym;
	long long val;
	struct symbol* left;
	struct symbol* right;
	char code[1000] = {0};
};

/*struct table {
	char a[256];
	struct symbol* sym;
	struct tree* left;
	struct tree* right;
}*/

#endif
