#include <stdio.h>
#include <string.h>
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

int _print_t(struct symbol *tree, int is_left, int offset, int depth, char s[20][255])
{
	char b[20];
	int width = 6;

	if (!tree) return 0;

	if (is_left)
		sprintf(b, "(%03d)0", tree->sym);
	else
		sprintf(b, "(%03d)1", tree->sym);


	int left  = _print_t(tree->left,  1, offset,				depth + 1, s);
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

int print_codes(struct symbol* table, FILE* t, Code* codes, bool screen) {
	static int i = 0;
	if (!table)
		return 0;
	if (!table->left && !table->right)
	{
		if(screen)
			printf("'%d' code: \"%s\"\n", table->sym, table->code);
		fprintf(t, "%d\t%s\n", table->sym, table->code);
		codes[i].sym = table->sym;
		strcpy(codes[i].code, table->code);
		i++;
		return 0;
	}
	print_codes(table->left, t, codes, screen);
	print_codes(table->right, t, codes, screen);
	return 0;
}

void print_help() {
	printf("-o <output_file>\tУказать имя выходного файла\n"\
			"-h, --help\t\tВывести эту справку\n"\
			"--screen\t\tВывести таблицу символов на экран(не отключает вывод в файл)\n"\
			"-i <input_file>\t\tФайл, данные из которого будут зашифрованы\n"\
			"-e, --enc\t\tЗашифровать данные\n"\
			"-d, --dec\t\tДешифровать данные\n"\
			"-t <table_file>\t\tФайл для записи кодовой таблицы\n");
}
