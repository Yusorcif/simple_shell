#include "shell.h"
/**
 * cstrlen - as defined
 * @s: the string to check
 *
 * Return: integer
 */
int cstrlen(char *s)
{
	int i = 0;

	if (!s)
		return (0);
	while (*s++)
		i++;
	return (i);
}
/**
 * mystrcmp - to compare
 * @s1: string one
 * @s2: string two
 *
 * Return: negative or positive or zero
 */
int mystrcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}
/**
 * start_hay - checks if it start with
 * @haystack: search string
 * @needle: the
 *
 * Return: address
 */
char *start_hay(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}
/**
 * cstrcat - concatenates string
 * @destn: the location
 * @src: the
 *
 * Return: returns pointer
 */
char *cstrcat(char *destn, char *src)
{
	char *resss = destn;

	while (*destn)
		destn++;
	while (*src)
		*destn++ = *src++;
	*destn = *src;
	return (resss);
}
