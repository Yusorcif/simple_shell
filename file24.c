#include "shell.h"

/**
 * r_vars - to replace var
 * @ayoinfo: the struct
 *
 * Return: 1 or 0
 */
int r_vars(ayoinfo_t *ayoinfo)
{
	int i = 0;
	mylist_t *node;

	for (i = 0; ayoinfo->argv[i]; i++)
	{
		if (ayoinfo->argv[i][0] != '$' || !ayoinfo->argv[i][1])
			continue;
		if (!mystrcmp(ayoinfo->argv[i], "$?"))
		{
			repstr(&(ayoinfo->argv[i]),
					cp_null(c_number(ayoinfo->status, 10, 0)));
			continue;
		}
		if (!mystrcmp(ayoinfo->argv[i], "$$"))
		{
			repstr(&(ayoinfo->argv[i]),
					cp_null(c_number(getpid(), 10, 0)));
			continue;
		}
		node = node_start_hay(ayoinfo->env, &ayoinfo->argv[i][1], '=');
		if (node)
		{
			repstr(&(ayoinfo->argv[i]),
					cp_null(cstrchr(node->str, '=') + 1));
			continue;
		}
		repstr(&ayoinfo->argv[i], cp_null(""));
	}
	return (0);
}
/**
 * repstr - replace str
 * @old: old
 * @new: new
 *
 * Return: 1 or 0
 */
int repstr(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
