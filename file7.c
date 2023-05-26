#include "shell.h"

/**
 **cstrncpy - copies a string
 *@destn: the destination string to be copied to
 *@src: the source string
 *@n: the amount of characters to be copied
 *Return: the concatenated string
 */
char *cstrncpy(char *destn, char *src, int n)
{
  int i, j;
  char *s = destn;

  i = 0;
  while (src[i] != '\0' && i < n - 1)
    {
      destn[i] = src[i];
      i++;
    }
  if (i < n)
    {
      j = i;
      while (j < n)
	{
	  destn[j] = '\0';
	  j++;
	}
    }
  return (s);
}

/**
 **cstrncat - concatenates two strings
 *@destn: the first string
 *@src: the second string
 *@n: the amount of bytes to be maximally used
 *Return: the concatenated string
 */
char *cstrncat(char *destn, char *src, int n)
{
  int i, j;
  char *s = destn;

  i = 0;
  j = 0;
  while (destn[i] != '\0')
    i++;
  while (src[j] != '\0' && j < n)
    {
      destn[i] = src[j];
      i++;
      j++;
    }
  if (j < n)
    destn[i] = '\0';
  return (s);
}

/**
 **cstrchr - locates a character in a string
 *@s: the string to be parsed
 *@c: the character to look for
 *Return: (s) a pointer to the memory area s
 */
char *cstrchr(char *s, char c)
{
  do {
    if (*s == c)
      return (s);
  } while (*s++ != '\0');

  return (NULL);
}
