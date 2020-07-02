#include "libtep.h"
#include <getopt.h>
#include "filehandler.c"

#define MAX_TITLE 30
#define MAX_AUTHOR 30

int ActionCommandLine(FILE*, int, char**, size_t, size_t);

int main(int argc, char **argv) 
{
	/*
		Read through "lib.txt" file, parse the lines into book structs and store these in a vector array.	
	 */

	FILE *lib_file = OpenFile("../lib.txt", "a", 0);
	size_t struct_size = 5;
	size_t max_length = MAX_TITLE + MAX_AUTHOR + (sizeof(unsigned int) * 3);	
	/*int rtn_code;*/

	if ( ActionCommandLine(lib_file, argc, argv, max_length, struct_size) < 1 ) {
		fprintf(stderr, "Error whilst parsing command line\n");
		exit(EXIT_FAILURE);
	}
	
}

int ActionCommandLine(FILE *fp, int argc, char **argv, size_t max_l_len, size_t struct_size)
{
	int opt;
	char *opt_str = "a:A;r:R:pP";
	book inp_book;

	while ((opt = getopt(argc, argv, opt_str)) != EOF ) {
		switch(opt) {
			case 'a':
			case 'r':
				inp_book = CslToStruct(optarg, max_l_len, struct_size);

				switch(opt) {
					case 'a':
						AddLine(fp, max_l_len, &inp_book, struct_size);	
						inp_book.line = CountLine(fp, max_l_len, 0);
						printf("Output: %s\n", StructToCsl(&inp_book, max_l_len, struct_size));
						break;
					case 'r':
						inp_book.line = FindLine(fp, inp_book.title, max_l_len);					
						RemoveLine(fp, max_l_len, &inp_book, struct_size);
					break;
				}
					
				break;
			
			case 'p':
				CountLine(fp, max_l_len, 1);
				break;
			case '?':
				fprintf(stderr, "Incorrect arugment found\n");
				return -1;
		}
	}

	if ( fp != NULL ) { fclose(fp); }	
	return 1;
}
