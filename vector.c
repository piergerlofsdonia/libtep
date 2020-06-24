#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define NUM_BOOKS 2

struct book 
{
	char *name;
	char *author;
	unsigned int pages;
	unsigned long ISBN;
	// short localisation; // Just emulating a system in which localised copies might be given an ID.
};

void InitaliseStruct(struct book *array_ptr, unsigned int array_size);
int ReallocateStruct(struct book *vec_ptr, unsigned int bytes_to_add);
int AddStructParams(struct book *vec_ptr, char *name, char *author, unsigned int pages, unsigned long ISBN);

int main() 
{
	unsigned int struct_size = 4;
	struct book *vec_array = (struct book *) malloc(sizeof(struct book) * NUM_BOOKS);
	InitaliseStruct(vec_array, NUM_BOOKS);
	// Implement command line parser to take in these arguments and format into flat struct then feed "AddStructParams" - will need changing
	if ( AddStructParams(&vec_array[0], "Title", "Author", 300, 123456789) <= 0 ) 
	{
		perror("Error whilst adding struct element values!\n"); exit(0);
	};
	
}

void InitaliseStruct(struct book *array_ptr, unsigned int array_size) 
{
	struct book blank_book = {"", "", 0, 0};
	int i;
	
	// Replace this with a realloc or malloc of the original pointer if needed.	
	if (!array_ptr) { perror("Initalisation error!\n"); exit(0); }

	for ( i = 0; i < array_size; i++ ) {
		array_ptr[i].name = blank_book.name;
		array_ptr[i].author = blank_book.author;
		array_ptr[i].pages = blank_book.pages;
		array_ptr[i].ISBN = blank_book.ISBN;
		
	}	
}

int AddStructParams(struct book *vec_ptr, char *name, char *author, unsigned int pages, unsigned long ISBN) 
{
	vec_ptr->name = name;
	vec_ptr->author = author;
	vec_ptr->pages = pages;
	vec_ptr->ISBN = ISBN;
	printf("The contents of %s are: %s, %u, %lu\n", vec_ptr->name, vec_ptr->author, vec_ptr->pages, vec_ptr->ISBN);
	return 1;
}
