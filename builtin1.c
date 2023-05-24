#include "shell.h"
#include <string.h>
/**
 * yushistory - this displays the history list,one command by line, preceded
 * with line numbers, starting at 0.
 * @yusinfo: structure containing potential arguments. Used to maintain
 * constant function prototype
 * Return: Always 0
 */
int yushistory(yusinfo_t *yusinfo)
{
	myprintlist(yusinfo->history);
	return (0);
}
/**
 * alias_to_string - set alias to string
 * @yusinfo: parameter struct
 * @str: the string alias
 * Return: 0 on success, 1 on error
 */
int alias_to_string(yusinfo_t *yusinfo, char *str)
{
	char *p, c;
	int resss;

	p = cstrchr(str, '=');
	if (!p)
	return (1);
	c = *p;
	*p = 0;
	resss = delnode(&(yusinfo->alias),
	g_node(yusinfo->alias, node_start_hay(yusinfo->alias, str, -1)));
	*p = c;
	return (resss);
}
/**
 * a_to_string - set alias to string
 * @yusinfo: parameter struct
 * @str: the string alias
 * Return: Always 0 on success, 1 on error
 */
int a_to_string(yusinfo_t *yusinfo, char *str)
{
	char *p;

	p = cstrchr(str, '=');
	if (!p)
	return (1);
	if (!*++p)
	return (alias_to_string(yusinfo, str));
	alias_to_string(yusinfo, str);
	return (a_n_e(&(yusinfo->alias), str, 0) == NULL);
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
	yus_puts(p + 1);
	yus_puts("'\n");
	return (0);
	}
	return (1);
}
/**
 * mimic_alias - mimics the alias builtin
 * @yusinfo: Structure containing potential arguments. Used to maintain
 * constant function prototypes
 * Return: Always 0
 */
int mimic_alias(yusinfo_t *yusinfo)
{
	int i = 0;
	char *p = NULL;
	mylist_t *node = NULL;

	if (yusinfo->argc == 1)
	{
	node = yusinfo->alias;
	while (node)
	{
	p_a(node);
	node = node->next;
	}
	return (0);
	}
	for (i = 1; yusinfo->argv[i]; i++)
	{
	p = cstrchr(yusinfo->argv[i], '=');
	if (p)
	a_to_string(yusinfo, ayoinfo->argv[i]);
	else
	p_a(node_start_hay(yusinfo->alias, yusinfo->argv[i], '='));
	}
	return (0);
}
