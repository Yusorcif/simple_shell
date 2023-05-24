#include "shell.h"
/**
 * clear_yusinfo - initializes yusinfo_t struct.
 * @yusinfo: struct address.
 */
void clear_yusinfo(yusinfo_t *yusinfo)
{

	yusinfo->arg = NULL;
	yusinfo->argv = NULL;
	yusinfo->path = NULL;
	yusinfo->argc = 0;
}

/**
 * set_yusinfo - initializes ayoinfo_t struct
 * @yusinfo: struct address
 * @av: argument vector
 */
void set_yusinfo(yusinfo_t *yusinfo, char **av)
{
	int i = 0;

	yusinfo->fname = av[0]
	if (yusinfo->arg)
	{
	yusinfo->argv = str_word(yusinfo->arg, " \t");
	if (!yusinfo->argv)
	{
	yusinfo->argv = malloc(sizeof(char *) * 2);
	if (yusinfo->argv)
	{
	yusinfo->argv[0] = cp_null(yusinfo->arg);
	yusinfo->argv[1] = NULL;
	}
	}
	for (i = 0; yusinfo->argv && yusinfo->argv[i]; i++)
	;
	yusinfo->argc = i;
	r_alias(yusinfo);
	r_vars(yusinfo);
	}
}

/**
 * free_yusinfo - frees yusinfo_t struct fields
 * @yusinfo: struct address
 * @all: true if freeing all fields
 */
void free_yusinfo(yusinfo_t *yusinfo, int all)
{
	afree(yusinfo->argv);
	yusinfo->argv = NULL;
	yusinfo->path = NULL;
	if (all)
	{
	if (!yusinfo->cmd_buf)
	free(yusinfo->arg);
	if (yusinfo->env)
	fr_list(&(yusinfo->env));
	if (yusinfo->history)
	fr_list(&(yusinfo->history));
	if (yusinfo->alias)
	fr_list(&(yusinfo->alias));
	afree(yusinfo->environ);
	yusinfo->environ = NULL;
	pfree((void **)yusinfo->cmd_buf);
	if (yusinfo->readmyfd > 2)
	close(yusinfo->readmyfd);
	__putchar(BUF_FLUSH);
	}
}
