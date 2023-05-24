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
