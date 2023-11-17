#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <stdbool.h>
#include <fcntl.h>
#include <errno.h>

/* read and write handler */
#define MAX_LENGTH 1024
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* chaining command chaincheck function page*/
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* number convertion handker */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define MAX_HIST	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - prototype for function pointer struct
 * @arg: a string generated from getline containing arguements
 * @argv: an array of strings generated from arg
 * @path: a string path for the current command
 * @argc: the argument count
 * @line_count: the error count
 * @err_num: the error code for exit()s
 * @linecount_flag: if on count this line of input
 * @fname: the program filename
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ from LL env
 * @history: the history node
 * @alias: the alias node
 * @env_changed: on if environ was changed
 * @status: the return status of the last exec'd command
 * @cmd_buf: address of pointer to cmd_buf, on if chaining
 * @cmd_buffer_type: CMD_type ||, &&, ;
 * @readfd: the fd from which to read line input
 * @histcount: the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buffer; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int counthist; /*count history*/
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 * struct builtin - contains a builtin string and related function
 * @type: the builtin command flag
 * @func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* shell main code`::q */
int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);

/* handle the parser*/
int ge_cmd(info_t *, char *);
char *dup_chars(char *, int, int);
char *ge_getpath(info_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* error handler.c */
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/* _string.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* function related to printf on strman.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _myputs(char *);
int _myputchar(char);

/* exits function */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* tokenizer handler */
char **strtow(char *, char *);
char **strtow2(char *, char);

/* memory realloc.c */
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* free_memory */
int bfree(void **);

/* atoi handler */
int interactive(info_t *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);

/* error handler functions */
int ge_erratoi(char *);
void print_errors(info_t *, char *);
int print_fdd(int, int);
char *convert_number(long int, int, int);
void ge_recomments(char *);

/* some builtin function handler */
int ge_myexit(info_t *);
int ge_mycd(info_t *);
int ge_myhelp(info_t *);

/* Dealing with history */
int ge_history(info_t *);
int ge_alias(info_t *);

/*in getline function */
ssize_t read_buf(info_t *info, char *buf, size_t *i);
ssize_t get_input(info_t *);
ssize_t input_buf(info_t *info, char **buf, size_t *len);
int _mygetline(info_t *, char **, size_t *);
void sigHandle(int);

/* Dealing with  */
void initiate_info(info_t *);
void set_info(info_t *, char **);
void free_fields(info_t *, int);

/* continue environ*/
char *ge_getenv(info_t *, const char *);
int ge_environ(info_t *info);
int ge_psetenv(info_t *info);
int ge_punsetenv(info_t *info);
int print_envlist(info_t *info);

/* environment fintion */
char **get_environ(info_t *info);
int ge_unsetenv(info_t *info, char *);
int ge_setenv(info_t *, char *, char *);

/* dealing with history*/
char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);

/* listhandler continue */
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_linklist(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_gelist(list_t **);

/* list handler conti*/
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_lists(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

/* checkchain page for chaining function*/
int isschain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int alias_replace(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);

#endif /*end of header file*/

