#include "shell.h"
/**
 * gethis - gets the history file
 * @yusinfo: parameter struct
 *
 * Return: allocated string containg history file
 */
char *gethis(yusinfo_t *yusinfo)
{
	char *buf, *dir;

	dir = yusgetenv(ayoinfo, "HOME=");
	if (!dir)
	return (NULL);
	buf = malloc(sizeof(char) * (cstrlen(dir) + cstrlen(HIST_FILE) + 2));
	if (!buf)
	return (NULL);
	buf[0] = 0;
	cstrcpy(buf, dir);
	cstrcat(buf, "/");
	cstrcat(buf, HIST_FILE);
	return (buf);
}

/**
 * w_history - creates a file, or appends to an existing file
 * @yusinfo: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int w_history(yusinfo_t *yusinfo)
{
	ssize_t fd;
	char *filename = gethis(yusinfo);
	mylist_t *node = NULL;

	if (!filename)
	return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
	return (-1);
	for (node = yusinfo->history; node; node = node->next)
	{
	printstr(node->str, fd);
	writefd('\n', fd);
	}
	writefd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * rdhist - reads history from file
 * @yusinfo: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int rdhist(yusinfo_t *yusinfo)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = gethis(ayoinfo);

	if (!filename)
	return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
	return (0);
	if (!fstat(fd, &st))
	fsize = st.st_size;
	if (fsize < 2)
	return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
	return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
	return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
	if (buf[i] == '\n')
	{
	buf[i] = 0;
	ayo_history_list(ayoinfo, buf + last, linecount++);
	last = i + 1;
	}
	if (last != i)
	yus_history_list(yusinfo, buf + last, linecount++);
	free(buf);
	yusinfo->histcount = linecount;
	while (yusinfo->histcount-- >= HIST_MAX)
	delnode(&(yusinfo->history), 0);
	renhist(yusinfo);
	return (yusinfo->histcount);
}

/**
 * yus_history_list - adds entry to a history linked list
 * @yusinfo: Structure containing potential arguments. Used to maintain
 * @buf: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */
int yus_history_list(yusinfo_t *yusinfo, char *buf, int linecount)
{
	mylist_t *node = NULL;

	if (yusinfo->history)
	node = yusinfo->history;
	a_n_e(&node, buf, linecount);

	if (!yusinfo->history)
	yusinfo->history = node;
	return (0);
}

/**
 * renhist - renumbers the history linked list after changes
 * @yusinfo: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int renhist(yusinfo_t *yusinfo)
{
	mylist_t *node = yusinfo->history;
	int i = 0;

	while (node)
	{
	node->num = i++;
	node = node->next;
	}
	return (yusinfo->histcount = i);
}
