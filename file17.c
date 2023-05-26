#include "shell.h"
/**
 **aymemset - to fill mem with con
 *@s: created to act as pointer
 *@b: as defined
 *@n: the number of bytes
 *Return: returns s
 */
char *aymemset(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;
	return (s);
}
/**
 * afree - frees a string of strings
 * @pp: string of strings
 */
void afree(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}
/**
 * ayrealloc - will reallocate memory
 * @ptr: to act as pointer to last allocation
 * @old_size: old size
 * @new_size: new size
 *
 * Return: it should
 */
void *ayrealloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);
	p = malloc(new_size);
	if (!p)
		return (NULL);
	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}
