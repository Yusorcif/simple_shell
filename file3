#include "shell.h"
#include <string.h>
/**
 * ayohistory - this displays the history list,one command by line, preceded
 * with line numbers, starting at 0.
 * @ayoinfo: structure containing potential arguments. Used to maintain
 * constant function prototype
 * Return: Always 0
 */
int ayohistory(ayoinfo_t *ayoinfo)
{
	myprintlist(ayoinfo->history);
	return (0);
}
/**
 * alias_to_string - set alias to string
 * @ayoinfo: parameter struct
 * @str: the string alias
 * Return: 0 on success, 1 on error
 */
int alias_to_string(ayoinfo_t *ayoinfo, char *str)
{
	char *p, c;
	int resss;

	p = cstrchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	resss = delnode(&(ayoinfo->alias),
			g_node(ayoinfo->alias, node_start_hay(ayoinfo->alias, str, -1)));
	*p = c;
	return (resss);
}
/**
 * a_to_string - set alias to string
 * @ayoinfo: parameter struct
 * @str: the string alias
 * Return: Always 0 on success, 1 on error
 */
int a_to_string(ayoinfo_t *ayoinfo, char *str)
{
	char *p;

	p = cstrchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (alias_to_string(ayoinfo, str));
	alias_to_string(ayoinfo, str);
	return (a_n_e(&(ayoinfo->alias), str, 0) == NULL);
}
/**
 * p_a - prints an alias string
 * @node: the node of the alias
 * Return: Always 0 on success, 1 on error
 */
int p_a(mylist_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = cstrchr(node->str, '=');
		for (a = node->str; a <= p; a++)
			__putchar(*a);
		__putchar('\'');
		ayo_puts(p + 1);
		ayo_puts("'\n");
		return (0);
	}
	return (1);
}
/**
 * mimic_alias - mimics the alias builtin
 * @ayoinfo: Structure containing potential arguments. Used to maintain
 * constant function prototypes
 * Return: Always 0
 */
int mimic_alias(ayoinfo_t *ayoinfo)
{
	int i = 0;
	char *p = NULL;
	mylist_t *node = NULL;

	if (ayoinfo->argc == 1)
	{
		node = ayoinfo->alias;
		while (node)
		{
			p_a(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; ayoinfo->argv[i]; i++)
	{
		p = cstrchr(ayoinfo->argv[i], '=');
		if (p)
			a_to_string(ayoinfo, ayoinfo->argv[i]);
		else
			p_a(node_start_hay(ayoinfo->alias, ayoinfo->argv[i], '='));
	}
	return (0);
}
