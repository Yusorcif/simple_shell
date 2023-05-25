#include "shell.h"
/**
 * ayoexit - exits the shell
 * @ayoinfo: structure containing potential arguments, used to maintain
 * constant function prototypes
 * Return: exits with a given exit status (0) if ayoinfo.argv[0] != "exit"
 */
int ayoexit(ayoinfo_t *ayoinfo)
{
  int checkexit;

  if (ayoinfo->argv[1])
    {
      checkexit = myerratoi(ayoinfo->argv[1]);
      if (checkexit == -1)
	{
	  ayoinfo->status = 2;
	  myprinterror(ayoinfo, "Illegal number: ");
	  myputs(ayoinfo->argv[1]);
	  myputchar('\n');
	  return (1);
	}
      ayoinfo->err_num = myerratoi(ayoinfo->argv[1]);
      return (-2);
    }
  ayoinfo->err_num = -1;
  return (-2);
}
/**
 * change_cd - changes the current directory of the process
 * @ayoinfo: structure containing the arguments.used to mantain constant
 * function prototypes
 * Return: Always 0
 */
int change_cd(ayoinfo_t *ayoinfo)
{
  char *s, *dir, buffer[1024];
  int chdir_ayo;

  s = getcwd(buffer, 1024);
  if (!s)
    ayo_puts("TODO: >>getcwd failure emsg here<<\n");
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
	  ayo_puts(s);
	  __putchar('\n');
	  return (1);
	}
      ayo_puts(ayogetenv(ayoinfo, "OLDPWD=")), __putchar('\n');
      chdir_ayo =
	chdir((dir = ayogetenv(ayoinfo, "OLDPWD=")) ? dir : "/");
    }
  else
    chdir_ayo = chdir(ayoinfo->argv[1]);
  if (chdir_ayo == -1)
    {
      myprinterror(ayoinfo, "can't cd to ");
      myputs(ayoinfo->argv[1]), myputchar('\n');
    }
  else
    {
      sssetenv(ayoinfo, "OLDPWD", ayogetenv(ayoinfo, "PWD="));
      sssetenv(ayoinfo, "PWD", getcwd(buffer, 1024));
    }
  return (0);
}
/**
 * change_p - this chn=anges the current directory of the process
 * @ayoinfo: structure containing potential arguments. used to maintain constant
 * function prototypes
 * Return: Always 0
 */
int change_p(ayoinfo_t *ayoinfo)
{
  char **arg_array;

  arg_array = ayoinfo->argv;
  ayo_puts("help call works. Function not yet implemented \n");
  if (0)
    ayo_puts(*arg_array);
  return (0);
}
