#include "shell.h"

/**
 * rdhist - to read
 * @ayoinfo: rep
 *
 * Return: return
 */
int rdhist(ayoinfo_t *ayoinfo)
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
		ayo_history_list(ayoinfo, buf + last, linecount++);
	free(buf);
	ayoinfo->histcount = linecount;
	while (ayoinfo->histcount-- >= HIST_MAX)
		delnode(&(ayoinfo->history), 0);
	renhist(ayoinfo);
	return (ayoinfo->histcount);
}

/**
 * ayo_history_list - add
 * @ayoinfo: struct
 * @buf: represents buffer
 * @linecount: count of history
 *
 * Return: Always 0
 */
int ayo_history_list(ayoinfo_t *ayoinfo, char *buf, int linecount)
{
	mylist_t *node = NULL;

	if (ayoinfo->history)
		node = ayoinfo->history;
	a_n_e(&node, buf, linecount);

	if (!ayoinfo->history)
		ayoinfo->history = node;
	return (0);
}

/**
 * renhist - this will number hsitory
 * @ayoinfo: struct
 *
 * Return: to represnt the new history count
 */
int renhist(ayoinfo_t *ayoinfo)
{
	mylist_t *node = ayoinfo->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (ayoinfo->histcount = i);
}
