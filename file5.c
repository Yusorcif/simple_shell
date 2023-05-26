#include "shell.h"
/**
 * myputs - prints an output string
 * @str: the string to be printed
 * Return: Nothing
 */
void myputs(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		myputchar(str[i]);
		i++;
	}
}
/**
 * myputchar - writes the character  c to stderr
 * @c: the character to print
 * Return: On success 1
 * on error, -1 is returned, and errno is set appropriately
 */
int myputchar(char c)
{
	static int i;
	static char buf[W_BUF_SIZE];

	if (c == BUF_FLUSH || i >= W_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}
/**
 * writefd - writes the character c to given fd
 * @c: the character to print
 * @fd: the filedescriptor to write to
 * Return: on success 1.
 * on error, -1 is returned, and errno is set appropriately
 */
int writefd(char c, int fd)
{
	static int i;
	static char buf[W_BUF_SIZE];

	if (c == BUF_FLUSH || i >= W_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}
/**
 * printstr - prints an input string
 * @str: the string to be printed
 * @fd: the filedescriptor
 * Return: the number of chars put
 */
int printstr(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += writefd(*str++, fd);
	}
	return (i);
}
