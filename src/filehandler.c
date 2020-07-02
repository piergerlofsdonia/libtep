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
static unsigned int CountLine(FILE*, size_t, unsigned int);
static char *ConcatString(char*, char*);
static char *itoa(int);
static book CslToStruct(char*, size_t, size_t);
static char *StructToCsl(book*, size_t, size_t);
static unsigned int FindLine(FILE*, char*, size_t);

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
	
	fp = freopen(filename, "a", fp);

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
	size_t uid_len = 5;
	char *uid = malloc(sizeof(char) * uid_len);
	unsigned int converted_uid;
	unsigned int current_line = 0;
	unsigned int target_line = to_rem->line;

	if ( fp != NULL ) {
		fp = freopen(filename, "r", fp);
	} else {
		fp = OpenFile(filename, "r", 0);
	}

	/* Parse out the uid (last value in the string) and compare against to_rem->uid */

	while(getline(&lp, &max_l_len, fp) != -1) {
		if ( current_line != to_rem->line ) {
			fprintf(n_fp, "%s", lp);
			printf("Line: %d - %s", current_line, lp);
		} else {
			memcpy(uid, lp+(strlen(lp)-uid_len), uid_len);
			uid[uid_len-1] = '\0';
			converted_uid = atoi(uid);
			if ( converted_uid == getuid()) {	
				printf("Found: %d [%s] - %s\n", current_line, uid, lp);
			} else {
				printf("Cannot remove line %d: you are not the owner of this record\n");
				fprintf(n_fp, "%s", lp);
				printf("Line: %d - %s", current_line, lp);
			}

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

static unsigned int CountLine(FILE *fp, size_t max_l_len, unsigned int print_bool)
{
	fp = freopen(filename, "r", fp);
	char *lp = NULL;
	unsigned int line = 0;

	if ( print_bool == 1 ) {
		printf("Format:\nTitle, Author, Pages, User\n\n");
	}

	while(getline(&lp, &max_l_len, fp) != -1) {
		if ( print_bool == 1 ) {
			printf("%s", lp);
		}
		line++;
	}
	
	return (line-1);
}

static unsigned int FindLine(FILE *fp, char *title_str, size_t max_l_len) 
{
	fp = freopen(filename, "r", fp);
	char *lp = NULL;
	unsigned int line_n = 0;
	unsigned int title_len = strlen(title_str);
	char *comp_str = (char *) malloc(sizeof(char) * title_len+1);

	while(getline(&lp, &max_l_len, fp) != EOF) {
		memcpy(comp_str, lp, title_len+1);
		comp_str[title_len] = '\0';
		printf("%s vs. %s\n", comp_str, title_str);
		if ( memcmp(title_str, comp_str, title_len) == 0 ) {
			free(comp_str);
			return line_n;
		}
		
		line_n++;

	}
	
	free(comp_str);
	fprintf(stderr, "Could not find a document in %s with the title: %s\n", filename, title_str);
	exit(1);
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

static book CslToStruct(char *inp_str, size_t max_l_len, size_t struct_size)
{
	book rtn_struct;
	book defaults = {"No Title", "No Author", 0, 0};

	unsigned int i = 0;
	unsigned int n = 0; 
	unsigned int c = 0;
	unsigned int p = 0;
	char **str_arr = calloc(struct_size, (sizeof(char) * max_l_len));
	unsigned int ps_len;

	inp_str = ConcatString(inp_str, ",");
	ps_len = strlen(inp_str);
	if ( ps_len > max_l_len ) { 
		fprintf(stderr, "Error [%d]: Input string is too long!\n", __LINE__);
		exit(EXIT_FAILURE);
	}

	for(; n < ps_len ; n++) {
		if ( (int)inp_str[n] == 44 ) { /* ASCII 44 is a comma */
			p = n-c; /* Position is current index minus the last 'current' position. */
			str_arr[i] = realloc(str_arr[i], p+1);
			memcpy(str_arr[i], inp_str + c, p+1);
			str_arr[i][p] = '\0';
			i++;
	
			if ( (int)inp_str[n+1] == 32 ) { /* ASCII 32 is whitespace */
				c = n + 2;
			} else {
				c = n + 1;
			}	

		}
		
	}

	free(inp_str);
	
	rtn_struct.title = (str_arr[0] != NULL) ? str_arr[0] : defaults.title ;
	rtn_struct.author = (str_arr[1] != NULL) ? str_arr[1] : defaults.author;
	rtn_struct.pages = (str_arr[2] != NULL) ? atoi(str_arr[2]) : defaults.pages;
	rtn_struct.uid = getuid(); 

	printf("Struct: %s - %s - %d - %d - %d\n", rtn_struct.title, rtn_struct.author, rtn_struct.pages, rtn_struct.uid);

	return rtn_struct;
}

static char *StructToCsl(book *to_convert, size_t max_l_len, size_t struct_size)
{
	book defaults = {"No Title", "No Author", 0, 0};
	char **str_arr = malloc(sizeof(char *) * struct_size - 1);
	char *part_str = NULL;
	char *rtn_str = (char *) malloc(sizeof(char) * max_l_len);
	unsigned int i = 0;
	unsigned int p = 0;
	size_t str_len;

	
	str_arr[0] = to_convert->title; str_arr[1] = to_convert->author; 
	str_arr[2] = itoa(to_convert->pages); str_arr[3] = itoa(to_convert->uid);

	for ( ; i < struct_size-1; i++ ) {
		part_str = (i == struct_size-2) ? str_arr[i] : ConcatString(str_arr[i], ", ");
		str_len = strlen(part_str);
		memcpy(rtn_str+p, part_str, str_len);
		p += str_len;
	}

	rtn_str[p] = '\0';
	return rtn_str;
}
