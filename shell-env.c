#include "shell.h"
/**
 * my_e - prints the current environment
 * @yusinfo: structure conaining potential arguments. used to maintain constant
 * function prototype.
 * Return: Always 0
 */
int my_e(yusinfo_t *yusinfo)
{
	p_l_s(yusinfo->env);
	return (0);
}
/**
 * yusgetenv - gets the value of an environ variable
 * @yusinfo: structure containing potential arguments. used to maintain
 * @name: env var name
 * Return: the value
 */
char *yusgetenv(yusinfo_t *yusinfo, const char *name)
{
	mylist_t *node = yusinfo->env;
	char *p;

	while (node)
	{
	p = start_hay(node->str, name);
	if (p && *p)
	return (p);
	node = node->next;
	}
	return (NULL);
}
/**
 * yussetenv - initialize a new environment var, or modify exisiting 1
 * @yusinfo: structure containing potential arguments.Used to maintain constant
 * Return: Always 0
 */
int yussetenv(yusinfo_t *yusinfo)
{
	if (yusinfo->argc != 3)
	{
	myputs("Incorrect number of arguments\n");
	return (1);
	}
	if (sssetenv(yusinfo, yusinfo->argv[1], yusinfo->argv[2]))
	return (0);
	return (1);
}
/**
 * remove_env - Remove an environment variable
 * @yusinfo: Structure containing potential arguments. used to maintain
 * constant function prototypes
 * Return: Always 0
 */
int remove_env(yusinfo_t *yusinfo)
{
	int i;

	if (yusinfo->argc == 1)
	{
	myputs("Too few arguments.\n");
	return (1);
	}
	for (i = 1; i <= yusinfo->argc; i++)
	_remove_env(yuzinfo, yusinfo->argv[1]);
	return (0);
}
/**
 * p_env_list - populates env linked list
 * @yusinfo: structure containing potential arguments. used to maintain
 * constant function prototypes
 * Return: Always 0
 */
int p_env_list(yusinfo_t *yusinfo)
{
	mylist_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
	a_n_e(&node, environ[i], 0);
	yusinfo->env = node;
	return (0);
}
