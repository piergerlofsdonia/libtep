#include "libtep.h"
#include "filehandler.c"

#define MAX_TITLE 30
#define MAX_AUTHOR 30

int main(int argc, char **argv) 
{
	/*
		Read through "lib.txt" file, parse the lines into book structs and store these in a vector array.	
	 */

	/* AddLine test */
	book test_book = {"Book 4", "Author 4", 123, 3, getuid()};
	FILE *lib_file = OpenFile("../lib.txt", "a", 0);
	size_t struct_size = 5;
	size_t max_length = MAX_TITLE + MAX_AUTHOR + (sizeof(unsigned int) * 3);
	int rtn_code;
	rtn_code = AddLine(lib_file, max_length, &test_book, struct_size);

	/* TODO: Populate struct with line value using "ReadLine" */
	
	/* RemoveLine test */
	rtn_code = RemoveLine(lib_file, max_length, &test_book, struct_size);
	if ( rtn_code == 1 ) { fclose(lib_file); }	

}
