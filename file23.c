#include "shell.h"
/**
 * aychain - test if current char in buffer is a chain delimeter
 * @ayoinfo: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int aychain(ayoinfo_t *ayoinfo, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		ayoinfo->cmd_buf_type = C_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		ayoinfo->cmd_buf_type = C_AND;
	}
	else if (buf[j] == ';') /* found end of this command */
	{
		buf[j] = 0; /* replace semicolon with null */
		ayoinfo->cmd_buf_type = C_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}
/**
 * ch_chain - checks we should continue chaining based on last status
 * @ayoinfo: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 * @i: starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */
void ch_chain(ayoinfo_t *ayoinfo, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (ayoinfo->cmd_buf_type == C_AND)
	{
		if (ayoinfo->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (ayoinfo->cmd_buf_type == C_OR)
	{
		if (!ayoinfo->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	*p = j;
}
/**
 * r_alias - replaces an aliases in the tokenized string
 * @ayoinfo: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int r_alias(ayoinfo_t *ayoinfo)
{
	int i;
	mylist_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = node_start_hay(ayoinfo->alias, ayoinfo->argv[0], '=');
		if (!node)
			return (0);
		free(ayoinfo->argv[0]);
		p = cstrchr(node->str, '=');
		if (!p)
			return (0);
		p = cp_null(p + 1);
		if (!p)
			return (0);
		ayoinfo->argv[0] = p;
	}
	return (1);
}
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

