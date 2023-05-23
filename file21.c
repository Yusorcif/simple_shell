#include "shell.h"
/**
 * gethis - gets the history file
 * @ayoinfo: parameter struct
*
 * Return: allocated string containg history file
 */
char *gethis(ayoinfo_t *ayoinfo)
{
char *buf, *dir;

dir = ayogetenv(ayoinfo, "HOME=");
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
 * @ayoinfo: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int w_history(ayoinfo_t *ayoinfo)
{
ssize_t fd;
char *filename = gethis(ayoinfo);
mylist_t *node = NULL;

if (!filename)
return (-1);

fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
free(filename);
if (fd == -1)
return (-1);
for (node = ayoinfo->history; node; node = node->next)
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
 * @ayoinfo: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
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
 * ayo_history_list - adds entry to a history linked list
 * @ayoinfo: Structure containing potential arguments. Used to maintain
 * @buf: buffer
 * @linecount: the history linecount, histcount
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
 * renhist - renumbers the history linked list after changes
 * @ayoinfo: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
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
