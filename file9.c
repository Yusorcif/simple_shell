#include "shell.h"
/**
 * clear_ayoinfo - initializes ayoinfo_t struct.
 * @ayoinfo: struct address.
 */
void clear_ayoinfo(ayoinfo_t *ayoinfo)
{
	ayoinfo->arg = NULL;
	ayoinfo->argv = NULL;
	ayoinfo->path = NULL;
	ayoinfo->argc = 0;
}

/**
 * set_ayoinfo - initializes ayoinfo_t struct
 * @ayoinfo: struct address
 * @av: argument vector
 */
void set_ayoinfo(ayoinfo_t *ayoinfo, char **av)
{
	int i = 0;

	ayoinfo->fname = av[0];
	if (ayoinfo->arg)
	{
		ayoinfo->argv = str_word(ayoinfo->arg, " \t");
		if (!ayoinfo->argv)
		{

			ayoinfo->argv = malloc(sizeof(char *) * 2);
			if (ayoinfo->argv)
			{
				ayoinfo->argv[0] = cp_null(ayoinfo->arg);
				ayoinfo->argv[1] = NULL;
			}
		}
		for (i = 0; ayoinfo->argv && ayoinfo->argv[i]; i++)
			;
		ayoinfo->argc = i;

		r_alias(ayoinfo);
		r_vars(ayoinfo);
	}
}

/**
 * free_ayoinfo - frees ayoinfo_t struct fields
 * @ayoinfo: struct address
 * @all: true if freeing all fields
 */
void free_ayoinfo(ayoinfo_t *ayoinfo, int all)
{
	afree(ayoinfo->argv);
	ayoinfo->argv = NULL;
	ayoinfo->path = NULL;
	if (all)
	{
		if (!ayoinfo->cmd_buf)
			free(ayoinfo->arg);
		if (ayoinfo->env)
			fr_list(&(ayoinfo->env));
		if (ayoinfo->history)
			fr_list(&(ayoinfo->history));
		if (ayoinfo->alias)
			fr_list(&(ayoinfo->alias));
		afree(ayoinfo->environ);
			ayoinfo->environ = NULL;
		pfree((void **)ayoinfo->cmd_buf);
		if (ayoinfo->readmyfd > 2)
			close(ayoinfo->readmyfd);
		__putchar(BUF_FLUSH);
	}
}
