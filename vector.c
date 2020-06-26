#ifdef __STDC_ALLOC_LIB__
#define __STDC_WANT_LIB_EXT2__ 1
#else
#define _POSIX_C_SOURCE 200809L
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_TITLE_LENGTH 30
#define MAX_AUTHOR_LENGTH 30
#define MAX_PAGE_DIGITS 5
#define MAX_ISBN 13

struct book 
{
	char *name;
	char *author;
	unsigned int pages;
	unsigned long isbn;
	// short localisation; // Just emulating a system in which localised copies might be given an ID.
};

char *ConcatenateString(char *str, char* str_to_add);
void AllocateInputString(char **ptr_arr, unsigned int struct_size);
void ParseInputString(char **str_ptr_arr, char *input_string);
void InitaliseStruct(struct book *struct_ptr);
int ReallocateStruct(struct book *vec_ptr, unsigned int bytes_to_add);
int AddStructParams(struct book *vec_ptr, char **string_ptr);

int main() 
{
	const unsigned int struct_size = 4;
	unsigned int array_size = 1;
	unsigned int book_count = array_size;
	// Initalise vector array.
	
	struct book *vec_array = (struct book *) malloc(sizeof(struct book) * book_count);
	InitaliseStruct(&vec_array[0]);
		
	unsigned int line_length = (MAX_TITLE_LENGTH + MAX_AUTHOR_LENGTH + sizeof(unsigned int) + sizeof(unsigned long) + 6);
	// Initalise an array of char pointers.
	char **ptr_arr = malloc(struct_size * sizeof(char *));
	// Malloc for each element in the char pointer array.
	AllocateInputString(ptr_arr, struct_size);
	// Allocate memory for the input string from the terminal.	
	char *input_string = malloc(line_length);

	while(1)
	{
		printf("\nEnter a list of arguments to enter a book into the vector array: (e.g. Operating Systems, Arpaci-Dussea, 675, 198508649)\n");
		// Take an input line from the command-line of length equal to author+title+digits+spaces+commas.
		fgets(input_string, line_length, stdin);
		ParseInputString(ptr_arr, input_string);
		if ( book_count > array_size ) {
			vec_array = realloc(vec_array, sizeof(struct book) * book_count); 
			array_size = book_count;		
		}
		
		int rtn_code = AddStructParams(&vec_array[book_count-1], ptr_arr);
		if ( rtn_code <= 0 ) { perror("Error whilst adding struct element to array\n"); exit(0); 
		} else {
			printf("Size increase: vec_array size is: %lu bytes\n", sizeof(struct book) * book_count);	
			book_count++;
		}	
	}
}

void AllocateInputString(char **ptr_arr, unsigned int struct_size)
{
	int max_sizes[4] = { MAX_TITLE_LENGTH, MAX_AUTHOR_LENGTH, MAX_PAGE_DIGITS, MAX_ISBN };
	int i;
	for ( i = 0; i < struct_size; i++ ) {
		ptr_arr[i] = (char *) malloc(max_sizes[i]+1);
	}
}

void ParseInputString(char **str_ptr_arr, char *input_string) 
{
	/* 
		Parse input string from fgets, split at comma-space and put in string array.	
		An issue arises quickly with cli inputs in that a comma-seperated list either
		has to have a block of code that checks for the last word (not comma-seperated)
		or, in this case, simply concat a comma-seperation onto the input string and parse
		that instead.
	 */

	int s = 0; int n = 0; int a = 0; int p = 0; int i = 0;
	
	input_string = ConcatenateString(input_string, ", "); 
	char *part_string = calloc(1, 1);
	int string_length = strlen(input_string);

	for ( i = 0; i < string_length; i++ ) {
		if ( input_string[i] == 44 ) {
			// strncpy into array using dest, src + s, i-s.
			p = i-s;
			part_string = realloc(part_string, p+1);
			strncpy(part_string, input_string + s, p+1);
			part_string[p] = '\0';
			str_ptr_arr[n] = strdup(part_string);
			n++;

			if ( input_string[i+1] == 32 ) {
				a = 2; // Set start index.
			} else {
				a = 1;
			} // Could make this a case.
			
			s = i + a;
		} else if ( i == string_length - 1 ) {
		}
	}

	free(part_string);
	free(input_string);
	return;
}

char *ConcatenateString(char *str, char *str_to_add) 
{
	const size_t len_str = strlen(str); const size_t len_str_add = strlen(str_to_add);
	char *rtn_str = malloc(len_str + len_str_add + 1);
	memcpy(rtn_str, str, len_str);
	memcpy(rtn_str + len_str, str_to_add, len_str_add+1);
	return rtn_str;
}

void InitaliseStruct(struct book *struct_ptr) 
{
	struct book blank = {"", "", 0, 0};

	// Replace this with a realloc or malloc of the original pointer if needed.	
	if (!struct_ptr) { perror("Initalisation error!\n"); exit(0); }
	
	struct_ptr->name = blank.name;
	struct_ptr->author = blank.author;
	struct_ptr->pages = blank.pages;
	struct_ptr->isbn = blank.isbn;
}

int AddStructParams(struct book *vec_ptr, char **string_ptr) 
{
	unsigned int pages = atoi(string_ptr[2]);
	unsigned long isbn = atoi(string_ptr[3]);
	vec_ptr->name = string_ptr[0];
	vec_ptr->author = string_ptr[1];
	vec_ptr->pages = pages;
	vec_ptr->isbn = isbn;
	printf("The contents of %s are: %s, %u, %lu\n", vec_ptr->name, vec_ptr->author, vec_ptr->pages, vec_ptr->isbn);
	return 1;
}
