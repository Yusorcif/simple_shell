#include "shell.h"

/**
 * yusinter - returns true if shell is active
 * @yusinfo: struct address
 *
 * Return: 1 if interactive mode, 0
 */
int yusinter(yusinfo_t *yusinfo)
{
	return (isatty(STDIN_FILENO) && yuso->readfd <= 2);
}

/**
 * mydelim - checks if char is a delimeter
 * @c: the char to check
 * @yusdelim: the delimeter string
 * Return: 1 if true, 0 if false
 */
int mydelim(char c, char *yusdelim)
{
	while (*yusdelim)
	if (*yusdelim++ == c)
	return (1);
	return (0);
}

/**
 * _isalpha - checks for alphabetic char
 * @c: The char to input
 * Return: 1 if c is alphabetic, otherwise 0
 */

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
	return (1);
	else
	return (0);
}
/**
 * myatoi - converts a string to integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 */

int myatoi(char *s)
{
	int i, mysign = 1, myflag = 0, myoutput;
	unsigned int myresult = 0;

	for (i = 0; s[i] != '\0' && myflag != 2; i++)
	{
	if (s[i] == '-')
	mysign *= -1;

	if (s[i] >= '0' && s[i] <= '9')
	{
	myflag = 1;
	myresult *= 10;
	myresult += (s[i] - '0');
	}
	else if (myflag == 1)
	myflag = 2;
	}
	if (mysign == -1)
	myoutput = -result;
	else
	myoutput = myresult;
	return (myoutput);
}
