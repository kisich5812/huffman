#include <stdio.h>
#include <stdlib.h>
#include "main.h"

int main(int argc, char* argv[])
{
	Flags* f = check_flags(argc, argv);
	if ( !f ) return 0;
	if (f->enc && f->dec) return -printf("Ошибка! Недопустима и расшифровка и дешифровка одновременно.\n");
	if (f->enc)
		main_enc(f);
	if (f->dec)
		main_dec(f);
	if (!f->enc && !f->dec) return -printf("Нечего делать!\n");
	free(f);

	return 0;
}
