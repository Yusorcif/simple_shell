#include "shell.h"

/**
 * ayoexit - exits the shell
 * @ayoinfo: Structure containing potential arguments
 * Return: exits with a given exit status
 * (0) if info.argv[0] != "exit"
 */
int ayoexit(ayoinfo_t *ayoinfo)
{
	int exitchecks;

	if (ayoinfo->argv[1]) /* If there is an exit arguement */
	{
	exitchecks = _erratoi(ayoinfo->argv[1]);
	if (exitchecks == -1)
	{
	ayoinfo->status = 2;
	myprint_error(ayoinfo, "Illegal number: ");
	myputs(info->argv[1]);
	myputchar('\n');
	return (1);
	}
	ayoinfo->err_num = _erratoi(ayoinfo->argv[1]);
	return (-2);
	}
	ayoinfo->err_num = -1;
	return (-2);
}
/**
 * change_cd - changes the current directory
 * @ayoinfo: Structure containing potential arguments
 * Return: Always 0
 */
int change_cd(ayoinfo_t *ayoinfo)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
	yus_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!ayoinfo->argv[1])
	{
	dir = ayogetenv(ayoinfo, "HOME=");
	if (!dir)
	chdir_ayo =
	chdir((dir = ayogetenv(ayoinfo, "PWD=")) ? dir : "/");
	else
	chdir_ayo = chdir(dir);
	}
	else if (mystrcmp(ayoinfo->argv[1], "-") == 0)
	{
	if (!ayogetenv(ayoinfo, "OLDPWD="))
	{
	my_puts(s);
	_putchar('\n');
	return (1);
	}
	my_puts(ayogetenv(ayoinfo, "OLDPWD=")), _putchar('\n');
	chdir_yus = /* TODO: what should this be? */
	chdir((dir = ayogetenv(ayoinfo, "OLDPWD=")) ? dir : "/");
	}
	else
	chdir_ayo = chdir(ayoinfo->argv[1]);
	if (chdir_ayo == -1)
	{
	myprint_error(ayoinfo, "can't cd to ");
	myputs(ayoinfo->argv[1]), _eputchar('\n');
	}
	else
	{
	_setenv(ayoinfo, "OLDPWD", _getenv(ayoinfo, "PWD="));
	_setenv(ayoinfo, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * change_p - changes the current directory
 * @ayoinfo: Structure containing potential arguments
 * Return: Always 0
 */
int change_p(ayoinfo_t *ayoinfo)
{
	char **arg_array;

	arg_array = ayoinfo->argv;
	ayo_puts("help call works. Function not yet implemented \n");
	if (0)
	ayo_puts(*arg_array); /* temp att_unused workaround */
	return (0);
}
