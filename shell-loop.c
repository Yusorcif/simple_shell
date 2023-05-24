#include "shell.h"

/**
 * yush - main shell loop
 * @yusinfo: the parameter & return ayoinfo struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int yush(yusinfo_t *yusinfo, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
	clear_yusinfo(yusinfo);
	if (yusinter(yusinfo))
	yus_puts("$ ");
	myputchar(BUF_FLUSH);
	r = agetinput(yusinfo);
	if (r != -1)
	{
	set_yusinfo(yusinfo, av);
	builtin_ret = find_b(yusinfo);
	if (builtin_ret == -1)
	f_cmd(yusinfo);
	}
	else if (yusinter(yusinfo))
	__putchar('\n');
	free_yusinfo(yusinfo, 0);
	}
	w_history(yusinfo);
	free_yusinfo(yusinfo, 1);
	if (!ayointer(ayoinfo) && yusinfo->status)
	exit(yusinfo->status);
	if (builtin_ret == -2)
	{
	if (yusinfo->err_num == -1)
	exit(yusinfo->status);
	exit(yusinfo->err_num);
	}
	return (builtin_ret);
}

/**
 * find_b - finds a builtin command
 * @yusinfo: the parameter & return ayoinfo struct
 *
 * Return: -1 if builtin not found,
 *0 if builtin executed successfully,
 *1 if builtin found but not successful,
 *-2 if builtin signals exit()
 */
int find_b(yusinfo_t *yusinfo)
{
	int i, built_in_ret = -1;

	b_table myb[] = {
	{"exit", yusexit},
	{"env", my_e},
	{"help", change_p},
	{"history", yushistory},
	{"setenv", yussetenv},
	{"unsetenv", remove_env},
	{"cd", change_cd},
	{"alias", mimic_alias},
	{NULL, NULL}
	};

	for (i = 0; myb[i].type; i++)
	if (mystrcmp(yusinfo->argv[0], myb[i].type) == 0)
	{
	yusinfo->line_count++;
	built_in_ret = myb[i].func(yusinfo);
	break;
	}
	return (built_in_ret);
}

/**
 * f_cmd - finds a command in PATH
 * @yusinfo: the parameter & return ayoinfo struct
 *
 * Return: void
 */
void f_cmd(yusinfo_t *yusinfo)
{
	char *path = NULL;
	int i, k;

	yusinfo->path = yusinfo->argv[0];
	if (yusinfo->linecount_myflag == 1)
	{
	yusinfo->line_count++;
	yusinfo->linecount_myflag = 0;
	}
	for (i = 0, k = 0; yusinfo->arg[i]; i++)
	if (!mydelim(yusinfo->arg[i], " \t\n"))
	k++;
	if (!k)
	return;

	path = f_path(yusinfo, yusgetenv(yusinfo, "PATH="), yusinfo->argv[0]);
	if (path)
	{
	yusinfo->path = path;
	fork_cmd(yusinfo);
	}
	else
	{
	if ((yusinter(yusinfo) || yusgetenv(yusinfo, "PATH=")
	|| yusinfo->argv[0][0] == '/') && yucmd(yusinfo, yusinfo->argv[0]))
	fork_cmd(yusinfo);
	else if (*(yusinfo->arg) != '\n')
	{
	yusinfo->status = 127;
	myprinterror(yusinfo, "not found\n");
	}
	}
}

/**
 * fork_cmd - forks a an exec thread to run cmd
 * @yusinfo: the parameter & return yusinfo struct
 *
 * Return: void
 */
void fork_cmd(yusinfo_t *yusinfo)
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
	if (execve(yusinfo->path, yusinfo->argv, g_env(yusinfo)) == -1)
	{
	free_yusinfo(yusinfo, 1);
	if (errno == EACCES)
	exit(126);
	exit(1);
	}
      /* TODO: PUT ERROR FUNCTION */
	}
	else
	{
	wait(&(yusinfo->status));
	if (WIFEXITED(yusinfo->status))
	{
	yusinfo->status = WEXITSTATUS(yusinfo->status);
	if (yusinfo->status == 126)
	myprinterror(yusinfo, "Permission denied\n");
	}
	}
}
