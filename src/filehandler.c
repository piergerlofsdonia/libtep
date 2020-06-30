#define  _POSIX_C_SOURCE 200809L
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "libtep.h"

static FILE *OpenFile(char*, const char*, unsigned short);
static int AddLine(FILE*, size_t, book*, size_t);
static int RemoveLine(FILE*, size_t, book*, size_t);
static char *ConcatString(char*, char*);
static char *itoa(int);

static char *filename = "../lib.txt";

static FILE *OpenFile(char *inp_filename, const char *mode, unsigned short recurr)
{
	if (memcmp(inp_filename, filename, strlen(filename)) == 0 || inp_filename == NULL) {
		inp_filename = filename;
	}

	FILE *fp = fopen(inp_filename, mode);

	if ( fp == NULL ) {
		if ( recurr == 1 ) 
		{
			fprintf(stderr, "Error [%d]: Opening %s file\n", __LINE__, inp_filename);
			exit(EXIT_FAILURE);
		} else {
			printf("Creating %s file...\n", inp_filename);
			fp = OpenFile(inp_filename, "wb", 1);
			fp = freopen(inp_filename, mode, fp);
		}
	}

	return fp;

}

static int AddLine(FILE *fp, size_t max_l_len, book *to_add, size_t struct_size)
{
	if ( max_l_len <= 0 ) { perror("Invalid input length given to AddLine\n"); exit(EXIT_FAILURE); }
	char *line = (char *) malloc(max_l_len);
	char *concd_line;
	unsigned int line_n;
	unsigned int line_p = 0;
	unsigned int i;
		
	char **args_arr = malloc(sizeof(char *) * struct_size);
	
	args_arr[0] = to_add->title;
	args_arr[1] = to_add->author;
	args_arr[2] = itoa(to_add->pages);
	args_arr[3] = itoa(to_add->uid);

	/* Traverse struct and concatenate each element into a string */
	for (i=0; i<(struct_size-1); i++) {
		if ( i != (struct_size-2)) {
			concd_line = ConcatString(args_arr[i], ", ");
			line_n = strlen(concd_line);
			memcpy(line+line_p, concd_line, line_n);
		} else {
			line_n = strlen(args_arr[i]);
			memcpy(line+line_p, args_arr[i], line_n);
			free(concd_line);
		}
		
		line_p += line_n;

	}

	/* Add LineCount to populate struct->line */
	line[line_p] = '\0';
	printf("%s\n", line);	
	fprintf(fp, "%s\n", line);
	return 1;
}

static int RemoveLine(FILE *fp, size_t max_l_len, book *to_rem, size_t struct_size)
{
	/* Removes a line from the lib.txt file using the book->line variable */
	char *n_fn = "../lib_temp.txt";
	FILE *n_fp = OpenFile(n_fn, "w", 0);
	char *lp = NULL;
	unsigned int current_line = 0;
	unsigned int target_line = to_rem->line;
	if ( fp != NULL ) {
		fp = freopen(filename, "r", fp);
	} else {
		fp = OpenFile(filename, "r", 0);
	}

	while(getline(&lp, &max_l_len, fp) != -1) {
		if ( current_line != to_rem->line ) {
			fprintf(n_fp, "%s", lp);
			printf("Line: %d - %s", current_line, lp);
		}

		current_line++;
	}
	
	if ( remove(filename) == 0 ) {
		if ( rename(n_fn, filename) == 0 ) {
			fclose(n_fp);
			return 1;	
		}
	}

	return -1;
}

static char *ConcatString(char *o_str, char *a_str)
{
	const size_t len_o_str = strlen(o_str);
	const size_t len_a_str = strlen(a_str);
	char *rtn_str = malloc(len_o_str + len_a_str + 1);
	memcpy(rtn_str, o_str, len_o_str);
	memcpy(rtn_str + len_o_str, a_str, len_a_str+1);
	return rtn_str;
}

static char *itoa(int n) 
{
	char *str = (char *) calloc(1, sizeof(char) * sizeof(int)+1);
	sprintf(str, "%d", n);
	return str;
}
