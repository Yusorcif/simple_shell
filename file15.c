#include "shell.h"
/**
 * pfree - to fress pointer
 * @ptr: address of pointer
 *
 * Return: 1 or 0.
 */
int pfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
