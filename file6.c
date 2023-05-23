#include "shell.h"
/**
 * myerratoi - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string,  converted number otherwise
 * -1 on error
 */
int myerratoi(char *s)
{
	int i = 0;
	unsigned long int myresult = 0;

	if (*s == '+')
		s++;
	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			myresult *= 10;
			myresult += (s[i] - '0');
			if (myresult > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (myresult);
}
/**
 * myprinterror - prints an error message
 * @ayoinfo: the parameter & return ayoinfo struct
 * @estr: string containing specified error type
 * Return: 0 if no number in string, converted number otherwise -1 on error
 */
void myprinterror(ayoinfo_t *ayoinfo, char *estr)
{
	myputs(ayoinfo->fname);
	myputs(": ");
	print_dec(ayoinfo->line_count, STDERR_FILENO);
	myputs(": ");
	myputs(ayoinfo->argv[0]);
	myputs(": ");
	myputs(estr);
}
/**
 * print_dec - function prints a decimal (integer) number (base 10)
 * @input: the input
 * @fd: the filedescriptor to write to
 * Return: number of character printed
 */
int print_dec(int input, int fd)
{
	int (*___putchar)(char) = __putchar;
	int i, count = 0;
	unsigned int cdcd, current;

	if (fd == STDERR_FILENO)
		___putchar = myputchar;
	if (input < 0)
	{
		cdcd = -input;
		___putchar('-');
		count++;
	}
	else
		cdcd = input;
	current = cdcd;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (cdcd / i)
		{
			___putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	___putchar('0' + current);
	count++;
	return (count);
}
/**
 * c_number - converter function, a clone of itoa
 * @num: number
 * @base: base
 * @myflags: argument myflags
 * Return: string
 */
char *c_number(long int num, int base, int myflags)
{
	static char *array;
	static char buffer[50];
	char mysign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(myflags & C_UNSIGNED) && num < 0)
	{
		n = -num;
		mysign = '-';
	}
	array = myflags & C_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';
	do {
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);
	if (mysign)
		*--ptr = mysign;
	return (ptr);
}
/**
 * c_comments - function replaces first instance of '#' with '\0'
 * @buf: address of the string to modify
 * Return: Always 0;
 */
void c_comments(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
}
