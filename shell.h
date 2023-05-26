#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

#define READ_BUF_SIZE 1024
#define W_BUF_SIZE 1024
#define BUF_FLUSH -1

#define C_NORM	0
#define C_OR		1
#define C_AND		2
#define C_CHAIN	3

#define C_LOWERCASE	1
#define C_UNSIGNED	2

#define C_GETLINE 0
#define C_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - create linked list
 * @num: rep numb
 * @str: strn
 * @next: pointer
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} mylist_t;

/**
 *struct passayoinfo - as defined
 *@arg: a ard
 *@argv: an arra
 *@path: a path
 *@argc: the argc
 *@line_count: the count
 *@err_num: the error
 *@linecount_myflag: if count
 *@fname: file name of pr
 *@env: environment
 *@environ: coy of env
 *@history: the history
 *@alias: the alias
 *@env_changing: for changed env
 *@status: the return status last com
 *@cmd_buf: as defined
 *@cmd_buf_type: Check code
 *@readmyfd: as said
 *@histcount: to count
 */
typedef struct passayoinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_myflag;
	char *fname;
	mylist_t *env;
	mylist_t *history;
	mylist_t *alias;
	char **environ;
	int env_changing;
	int status;

	char **cmd_buf;
	int cmd_buf_type;
	int readmyfd;
	int histcount;
} ayoinfo_t;

#define AYOINFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - my builtin
 *@type: the myflag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(ayoinfo_t *);
} b_table;


int aysh(ayoinfo_t *, char **);
int find_b(ayoinfo_t *);
void f_cmd(ayoinfo_t *);
void fork_cmd(ayoinfo_t *);

int aycmd(ayoinfo_t *, char *);
char *d_chars(char *, int, int);
char *f_path(ayoinfo_t *, char *, char *);

int loopaysh(char **);

void myputs(char *);
int myputchar(char);
int writefd(char c, int fd);
int printstr(char *str, int fd);

int cstrlen(char *);
int mystrcmp(char *, char *);
char *start_hay(const char *, const char *);
char *cstrcat(char *, char *);

char *cstrcpy(char *, char *);
char *cp_null(const char *);
void ayo_puts(char *);
int __putchar(char);

char *cstrncpy(char *, char *, int);
char *cstrncat(char *, char *, int);
char *cstrchr(char *, char);

char **str_word(char *, char *);
char **str_wordd(char *, char);

char *aymemset(char *, char, unsigned int);
void afree(char **);
void *ayrealloc(void *, unsigned int, unsigned int);

int pfree(void **);

int ayointer(ayoinfo_t *);
int mydelim(char, char *);
int _isalpha(int);
int myatoi(char *);

int myerratoi(char *);
void myprinterror(ayoinfo_t *, char *);
int print_dec(int, int);
char *c_number(long int, int, int);
void c_comments(char *);

int ayoexit(ayoinfo_t *);
int change_cd(ayoinfo_t *);
int change_p(ayoinfo_t *);

int ayohistory(ayoinfo_t *);
int mimic_alias(ayoinfo_t *);

ssize_t agetinput(ayoinfo_t *);
int agetline(ayoinfo_t *, char **, size_t *);
void handle_sig(int);

void clear_ayoinfo(ayoinfo_t *);
void set_ayoinfo(ayoinfo_t *, char **);
void free_ayoinfo(ayoinfo_t *, int);

char *ayogetenv(ayoinfo_t *, const char *);
int my_e(ayoinfo_t *);
int ayosetenv(ayoinfo_t *);
int remove_env(ayoinfo_t *);
int p_env_list(ayoinfo_t *);

char **g_env(ayoinfo_t *);
int _remove_env(ayoinfo_t *, char *);
int sssetenv(ayoinfo_t *, char *, char *);

char *gethis(ayoinfo_t *ayoinfo);
int w_history(ayoinfo_t *ayoinfo);
int rdhist(ayoinfo_t *ayoinfo);
int ayo_history_list(ayoinfo_t *ayoinfo, char *buf, int linecount);
int renhist(ayoinfo_t *ayoinfo);

mylist_t *add_node(mylist_t **, const char *, int);
mylist_t *a_n_e(mylist_t **, const char *, int);
size_t p_l_s(const mylist_t *);
int delnode(mylist_t **, unsigned int);
void fr_list(mylist_t **);

size_t lenlin(const mylist_t *);
char **l_to_str(mylist_t *);
size_t myprintlist(const mylist_t *);
mylist_t *node_start_hay(mylist_t *, char *, char);
ssize_t g_node(mylist_t *, mylist_t *);

int aychain(ayoinfo_t *, char *, size_t *);
void ch_chain(ayoinfo_t *, char *, size_t *, size_t, size_t);
int r_alias(ayoinfo_t *);
int r_vars(ayoinfo_t *);
int repstr(char **, char *);

#endif
