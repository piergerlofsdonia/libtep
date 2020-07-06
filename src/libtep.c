#include "libtep.h"
#include <getopt.h>
#include <unistd.h>
#include "filehandler.c"

#define MAX_TITLE 30
#define MAX_AUTHOR 30

int ActionCommandLine(FILE*, int, char**, size_t, size_t);
char *SetupFileSystem();

int main(int argc, char **argv) 
{
	SetupFilePath();
	FILE *lib_file = OpenFile(filename, "a", 0);
	size_t struct_size = 5;
	size_t max_length = MAX_TITLE + MAX_AUTHOR + (sizeof(unsigned int) * 3);	

	if ( ActionCommandLine(lib_file, argc, argv, max_length, struct_size) < 1 ) {
		fprintf(stderr, "Error whilst parsing command line\n");
		exit(EXIT_FAILURE);
	}
		
}

int ActionCommandLine(FILE *fp, int argc, char **argv, size_t max_l_len, size_t struct_size)
{
	int opt;
	char *opt_str = "a:A;r:R:pPhH";
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
						break;
					case 'r':
						inp_book.line = FindLine(fp, inp_book.title, max_l_len);					
						RemoveLine(fp, max_l_len, &inp_book, struct_size);
					break;
				}
					
				break;
			case 'h':
				FindAndPrint("../README.md", "Help", max_l_len);		
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

