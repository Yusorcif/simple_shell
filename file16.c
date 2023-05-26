#include "shell.h"
/**
 * aycmd - to check if it's executable
 * @ayoinfo: the struct named
 * @path: the defined path
 *
 * Return: 1 if success, 0 failed
 */
int aycmd(ayoinfo_t *ayoinfo, char *path)
{
	struct stat st;

	(void)ayoinfo;
	if (!path || stat(path, &st))
		return (0);
	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}
/**
 * d_chars - it will duplicate char
 * @pathstr: the str rep path
 * @start: the initial index
 * @stop: the end index
 *
 * Return: points to the new buffer
 */
char *d_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (pathstr[i] != ':')
			buf[k++] = pathstr[i];
	buf[k] = 0;
	return (buf);
}
/**
 * f_path - to find path
 * @ayoinfo: the struct created
 * @pathstr: the str path
 * @cmd: as defined
 *
 * Return: full path if okay
 */
char *f_path(ayoinfo_t *ayoinfo, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((cstrlen(cmd) > 2) && start_hay(cmd, "./"))
	{
		if (aycmd(ayoinfo, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = d_chars(pathstr, curr_pos, i);
			if (!*path)
				cstrcat(path, cmd);
			else
			{
				cstrcat(path, "/");
				cstrcat(path, cmd);
			}
			if (aycmd(ayoinfo, path))
				return (path);
			if (!pathstr[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}
