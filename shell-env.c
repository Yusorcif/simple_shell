#include "shell.h"
/**
 * my_e - prints the current environment
 * @ayoinfo: structure conaining potential arguments. used to maintain constant
 * function prototype.
 * Return: Always 0
 */
int my_e(ayoinfo_t *ayoinfo)
{
  p_l_s(ayoinfo->env);
  return (0);
}
/**
 * ayogetenv - gets the value of an environ variable
 * @ayoinfo: structure containing potential arguments. used to maintain
 * @name: env var name
 * Return: the value
 */
char *ayogetenv(ayoinfo_t *ayoinfo, const char *name)
{
  mylist_t *node = ayoinfo->env;
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
 * ayosetenv - initialize a new environment variable, or modify an exisiting
 * one
 * @ayoinfo: structure containing potential arguments. Used to maintain constant
 * function prototypes
 * Return: Always 0
 */
int ayosetenv(ayoinfo_t *ayoinfo)
{
  if (ayoinfo->argc != 3)
    {
      myputs("Incorrect number of arguments\n");
      return (1);
    }
  if (sssetenv(ayoinfo, ayoinfo->argv[1], ayoinfo->argv[2]))
    return (0);
  return (1);
}
/**
 * remove_env - Remove an environment variable
 * @ayoinfo: Structure containing potential arguments. used to maintain
 * constant function prototypes
 * Return: Always 0
 */
int remove_env(ayoinfo_t *ayoinfo)
{
  int i;

  if (ayoinfo->argc == 1)
    {
      myputs("Too few arguments.\n");
      return (1);
    }
  for (i = 1; i <= ayoinfo->argc; i++)
    _remove_env(ayoinfo, ayoinfo->argv[1]);
  return (0);
}
/**
 * p_env_list - populates env linked list
 * @ayoinfo: structure containing potential arguments. used to maintain
 * constant function prototypes
 * Return: Always 0
 */
int p_env_list(ayoinfo_t *ayoinfo)
{
  mylist_t *node = NULL;
  size_t i;

  for (i = 0; environ[i]; i++)
    a_n_e(&node, environ[i], 0);
  ayoinfo->env = node;
  return (0);
}
