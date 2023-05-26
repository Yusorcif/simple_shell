#include "shell.h"
/**
 * cstrcpy - created to copy str
 * @destn: the intended location
 * @src: source location
 * Return: pointer to location
 */
char *cstrcpy(char *destn, char *src)
{
	int i = 0;

	if (destn == src || src == 0)
		return (destn);
	while (src[i])
	{
		destn[i] = src[i];
		i++;
	}
	destn[i] = 0;
	return (destn);
}

/**
 * cp_null - this will duplicate
 * @str: to be duplicated
 *
 * Return: pointer
 */
char *cp_null(const char *str)
{
	int length = 0;
	char *resss;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	resss = malloc(sizeof(char) * (length + 1));
	if (!resss)
		return (NULL);
	for (length++; length--;)
		resss[length] = *--str;
	return (resss);
}

/**
 *ayo_puts - prints
 *@str: the strin
 *
 * Return: Nothing
 */
void ayo_puts(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		__putchar(str[i]);
		i++;
	}
}

/**
 * __putchar - wri
 * @c: The character
 *
 * Return: On
 */
int __putchar(char c)
{
	static int i;
	static char buf[W_BUF_SIZE];

	if (c == BUF_FLUSH || i >= W_BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}
