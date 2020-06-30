#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "libtep.h"

static FILE *OpenFile(char*, const char*, unsigned short);
static int AddLine(FILE*, size_t, book*, size_t);
static char *ConcatString(char*, char*);
static char *itoa(int);

/* Create itoa function */

static FILE *OpenFile(char *filename, const char *mode, unsigned short recurr)
{
	FILE *fp = fopen(filename, mode);

	if ( fp == NULL ) {
		if ( recurr == 1 ) 
		{
			fprintf(stderr, "Error [%d]: Opening %s file\n", __LINE__, filename);
			exit(EXIT_FAILURE);
		} else {
			printf("Creating %s file...\n", filename);
			fp = OpenFile(filename, "wb", 1);
			fp = freopen(filename, mode, fp);
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

	/*for ( i = 0; i < struct_size-1; i++ ) 
	{
		printf("%s\n", args_arr[i]);
	}*/

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
