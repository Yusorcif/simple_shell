#include "shell.h"
/**
 * g_env - returns the string array copy of our environ
 * @ayoinfo: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **g_env(ayoinfo_t *ayoinfo)
{
  if (!ayoinfo->environ || ayoinfo->env_changing)
    {
      ayoinfo->environ = l_to_str(ayoinfo->env);
      ayoinfo->env_changing = 0;
    }

  return (ayoinfo->environ);
}

/**
 * _remove_env - Remove an environment variable
 * @ayoinfo: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @var: the string env var property
 */
int _remove_env(ayoinfo_t *ayoinfo, char *var)
{
  mylist_t *node = ayoinfo->env;
  size_t i = 0;
  char *p;

  if (!node || !var)
    return (0);

  while (node)
    {
      p = start_hay(node->str, var);
      if (p && *p == '=')
	{
	  ayoinfo->env_changing = delnode(&(ayoinfo->env), i);
	  i = 0;
	  node = ayoinfo->env;
	  continue;
	}
      node = node->next;
      i++;
    }
  return (ayoinfo->env_changing);
}

/**
 * sssetenv - Initialize a new environment variable,
 *             or modify an existing one
 * @ayoinfo: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string env var property
 * @value: the string env var value
 *  Return: Always 0
 */
int sssetenv(ayoinfo_t *ayoinfo, char *var, char *value)
{
  char *buf = NULL;
  mylist_t *node;
  char *p;

  if (!var || !value)
    return (0);

  buf = malloc(cstrlen(var) + cstrlen(value) + 2);
  if (!buf)
    return (1);
  cstrcpy(buf, var);
  cstrcat(buf, "=");
  cstrcat(buf, value);
  node = ayoinfo->env;
  while (node)
    {
      p = start_hay(node->str, var);
      if (p && *p == '=')
	{
	  free(node->str);
	  node->str = buf;
	  ayoinfo->env_changing = 1;
	  return (0);
	}
      node = node->next;
    }
  a_n_e(&(ayoinfo->env), buf, 0);
  free(buf);
  ayoinfo->env_changing = 1;
  return (0);
}
