#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "encdec.h"

int main_enc(Flags* f) {
	FILE* i_file = fopen(f->input_file, "r");
	FILE* t_file;
	FILE* o_file;	
	if (f->table_file) t_file = fopen(f->table_file, "w");
	 else t_file = fopen("table.huf", "w");
	if (f->output_file) o_file = fopen(f->output_file, "w");
	 else o_file = fopen("output.huf", "w");

	if (!(i_file && t_file && o_file))
		return -printf("Ошибка открытия файлов!");
	int val_sym = 0;
        struct symbol* alph = (struct symbol*) calloc(256, sizeof(struct symbol));
	alph = dif_sym(i_file, alph, &val_sym);
	struct symbol* table = make_table(alph, val_sym);
	codes(table, NULL, -1);
	
	fprintf(t_file, "%d\n", val_sym);
	Code* codes = (Code*)calloc(val_sym, sizeof(Code));
	print_codes(table, t_file, codes, f->screen);

	destroy_table(table);
	free(alph);
	
	rewind(i_file);

	int c = fgetc(i_file);
	while(c != EOF) {
		for(int i = 0; i<val_sym; i++)
			if (c == codes[i].sym)
				fprintf(o_file, "%s", codes[i].code);
		c = fgetc(i_file);
	}
	
	free(codes);
	fclose(i_file);
	fclose(o_file);
	fclose(t_file);
	return 0;
}

int main_dec(Flags* f) {
	FILE* i_file = fopen(f->input_file, "r");
	FILE* t_file;
	FILE* o_file;	
	if (f->table_file) t_file = fopen(f->table_file, "r");
	 else return printf("Не задан файл с таблицей!\n"), -1;
	if (f->output_file) o_file = fopen(f->output_file, "w");
	 else o_file = fopen("output.txt", "w");

	if (!(i_file && t_file && o_file))
		return -printf("Ошибка открытия файлов!");

	int val_sym = 0;
	fscanf(t_file, "%d", &val_sym);

	Code* codes = (Code*)calloc(val_sym, sizeof(Code));
	for(int i = 0; i<val_sym; i++)
	{
		fscanf(t_file, "%d", &codes[i].sym);
		fscanf(t_file, "%s", &codes[i].code);
	}

	char* text = NULL;
	size_t len = 0;
	
	bool find = 0;
	getline(&text, &len, i_file);
	int n;
	while(strlen(text)>0) {
		n = 1;
		find = 0;
		while(true) {
			for(int i = 0; i<val_sym; i++) {
				if (check_code(text, codes[i].code, n) == 0) {
					fprintf(o_file, "%c", codes[i].sym);
					find = 1;
					break;
				}
			}
			if (find) {
				text += n;
				break;
			}
			else n++;
		}
	}

	free(codes);
	return 0;
}

int check_code(char* a, char* b, int n)
{
	if (strlen(b) != n)
		return -1;
	for(int i = 0; i<n; i++)
		if(a[i]!=b[i])
			return -1;
	return 0;
}
