#include "shell.h"

/**
 * yusexit - exits the shell
 * @yusinfo: Structure containing potential arguments
 * Return: exits with a given exit status
 * (0) if info.argv[0] != "exit"
 */
int yusexit(yusinfo_t *yusinfo)
{
	int exitchecks;

	if (yusinfo->argv[1]) /* If there is an exit arguement */
	{
	exitchecks = _erratoi(yusinfo->argv[1]);
	if (exitchecks == -1)
	{
	yusinfo->status = 2;
	myprint_error(yusinfo, "Illegal number: ");
	myputs(info->argv[1]);
	my`putchar('\n');
	return (1);
	}
	yusinfo->err_num = _erratoi(yusinfo->argv[1]);
	return (-2);
	}
	yusinfo->err_num = -1;
	return (-2);
}
/**
 * change_cd - changes the current directory
 * @yusinfo: Structure containing potential arguments
 * Return: Always 0
 */
int change_cd(yusinfo_t *yusinfo)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
	yus_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!yusinfo->argv[1])
	{
	dir = yusgetenv(yusinfo, "HOME=");
	if (!dir)
	chdir_yus =
	chdir((dir = yusgetenv(yusinfo, "PWD=")) ? dir : "/");
	else
	chdir_yus = chdir(dir);
	}
	else if (mystrcmp(yusinfo->argv[1], "-") == 0)
	{
	if (!yusgetenv(yusinfo, "OLDPWD="))
	{
	my_puts(s);
	_putchar('\n');
	return (1);
	}
	my_puts(yusgetenv(yusinfo, "OLDPWD=")), _putchar('\n');
	chdir_yus = /* TODO: what should this be? */
	chdir((dir = yusgetenv(yusinfo, "OLDPWD=")) ? dir : "/");
	}
	else
	chdir_yus = chdir(yusinfo->argv[1]);
	if (chdir_yus == -1)
	{
	myprint_error(yusinfo, "can't cd to ");
	myputs(yusinfo->argv[1]), _eputchar('\n');
	}
	else
	{
	_setenv(yusinfo, "OLDPWD", _getenv(yusinfo, "PWD="));
	_setenv(yusinfo, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * change_p - changes the current directory
 * @yusinfo: Structure containing potential arguments
 * Return: Always 0
 */
int change_p(yusinfo_t *yusinfo)
{
	char **arg_array;

	arg_array = yusinfo->argv;
	yus_puts("help call works. Function not yet implemented \n");
	if (0)
	yus_puts(*arg_array); /* temp att_unused workaround */
	return (0);
}
