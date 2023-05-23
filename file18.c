#include "shell.h"
/**
 * cstrcpy - copies a string
 * @destn: the destination
 * @src: the source
*
 * Return: pointer to destination
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
 * cp_null - duplicates a string
 * @str: the string to duplicate
 *
 * Return: pointer to the duplicated string
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
 *ayo_puts - prints an input string
 *@str: the string to be printed
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
 * __putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
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
