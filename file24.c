#include "shell.h"

/**
 * r_vars - replaces vars in the tokenized string
 * @ayoinfo: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
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
 * repstr - replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int repstr(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
