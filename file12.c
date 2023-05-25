#include "shell.h"

/**
 * aysh - main shell loop
 * @ayoinfo: the parameter & return ayoinfo struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int aysh(ayoinfo_t *ayoinfo, char **av)
{
  ssize_t r = 0;
  int builtin_ret = 0;

  while (r != -1 && builtin_ret != -2)
    {
      clear_ayoinfo(ayoinfo);
      if (ayointer(ayoinfo))
	ayo_puts("$ ");
      myputchar(BUF_FLUSH);
      r = agetinput(ayoinfo);
      if (r != -1)
	{
	  set_ayoinfo(ayoinfo, av);
	  builtin_ret = find_b(ayoinfo);
	  if (builtin_ret == -1)
	    f_cmd(ayoinfo);
	}
      else if (ayointer(ayoinfo))
	__putchar('\n');
      free_ayoinfo(ayoinfo, 0);
    }
  w_history(ayoinfo);
  free_ayoinfo(ayoinfo, 1);
  if (!ayointer(ayoinfo) && ayoinfo->status)
    exit(ayoinfo->status);
  if (builtin_ret == -2)
    {
      if (ayoinfo->err_num == -1)
	exit(ayoinfo->status);
      exit(ayoinfo->err_num);
    }
  return (builtin_ret);
}

/**
 * find_b - finds a builtin command
 * @ayoinfo: the parameter & return ayoinfo struct
 *
 * Return: -1 if builtin not found,
 *0 if builtin executed successfully,
 *1 if builtin found but not successful,
 *-2 if builtin signals exit()
 */
int find_b(ayoinfo_t *ayoinfo)
{
  int i, built_in_ret = -1;

  b_table myb[] = {
    {"exit", ayoexit},
    {"env", my_e},
    {"help", change_p},
    {"history", ayohistory},
    {"setenv", ayosetenv},
    {"unsetenv", remove_env},
    {"cd", change_cd},
    {"alias", mimic_alias},
    {NULL, NULL}
  };

  for (i = 0; myb[i].type; i++)
    if (mystrcmp(ayoinfo->argv[0], myb[i].type) == 0)
      {
	ayoinfo->line_count++;
	built_in_ret = myb[i].func(ayoinfo);
	break;
      }
  return (built_in_ret);
}

/**
 * f_cmd - finds a command in PATH
 * @ayoinfo: the parameter & return ayoinfo struct
 *
 * Return: void
 */
void f_cmd(ayoinfo_t *ayoinfo)
{
  char *path = NULL;
  int i, k;

  ayoinfo->path = ayoinfo->argv[0];
  if (ayoinfo->linecount_myflag == 1)
    {
      ayoinfo->line_count++;
      ayoinfo->linecount_myflag = 0;
    }
  for (i = 0, k = 0; ayoinfo->arg[i]; i++)
    if (!mydelim(ayoinfo->arg[i], " \t\n"))
      k++;
  if (!k)
    return;

  path = f_path(ayoinfo, ayogetenv(ayoinfo, "PATH="), ayoinfo->argv[0]);
  if (path)
    {
      ayoinfo->path = path;
      fork_cmd(ayoinfo);
    }
  else
    {
      if ((ayointer(ayoinfo) || ayogetenv(ayoinfo, "PATH=")
	   || ayoinfo->argv[0][0] == '/') && aycmd(ayoinfo, ayoinfo->argv[0]))
	fork_cmd(ayoinfo);
      else if (*(ayoinfo->arg) != '\n')
	{
	  ayoinfo->status = 127;
	  myprinterror(ayoinfo, "not found\n");
	}
    }
}

/**
 * fork_cmd - forks a an exec thread to run cmd
 * @ayoinfo: the parameter & return ayoinfo struct
 *
 * Return: void
 */
void fork_cmd(ayoinfo_t *ayoinfo)
{
  pid_t child_pid;

  child_pid = fork();
  if (child_pid == -1)
    {
      /* TODO: PUT ERROR FUNCTION */
      perror("Error:");
      return;
    }
  if (child_pid == 0)
    {
      if (execve(ayoinfo->path, ayoinfo->argv, g_env(ayoinfo)) == -1)
	{
	  free_ayoinfo(ayoinfo, 1);
	  if (errno == EACCES)
	    exit(126);
	  exit(1);
	}
      /* TODO: PUT ERROR FUNCTION */
    }
  else
    {
      wait(&(ayoinfo->status));
      if (WIFEXITED(ayoinfo->status))
	{
	  ayoinfo->status = WEXITSTATUS(ayoinfo->status);
	  if (ayoinfo->status == 126)
	    myprinterror(ayoinfo, "Permission denied\n");
	}
    }
}
