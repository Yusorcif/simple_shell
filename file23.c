#include "shell.h"
/**
 * aychain - to test for buf or del
 * @ayoinfo: the struct
 * @buf: the def buff
 * @p: address
 *
 * Return: 1 or 0
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
	else if (buf[j] == ';')
	{
		buf[j] = 0;
		ayoinfo->cmd_buf_type = C_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}
/**
 * ch_chain - as defined
 * @ayoinfo: the struct
 * @buf: the
 * @p: rep addres
 * @i: beg buf position
 * @len: length
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
 * r_alias - to replace alias
 * @ayoinfo: the parameter defined
 *
 * Return: 1 or  0
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
