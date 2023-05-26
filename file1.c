#include "shell.h"

/**
 * ayointer - returns true if shell is in interactive mode
 * @ayoinfo: struct address
 * Return: 1 if interactive mode, 0 otherwise
 */
int ayointer(ayoinfo_t *ayoinfo)
{
    return (isatty(STDIN_FILENO) && ayoinfo->readmyfd <= 2);
}

/**
 * mydelim - checks if character is a delimiter
 * @c: the character to check
 * @ayodelim: the delimiter string
 * Return: 1 if true, 0 if false
 */
int mydelim(char c, char *ayodelim)
{
    while (*ayodelim)
    {
        if (*ayodelim++ == c)
            return (1);
    }
    return (0);
}

/**
 * _isalpha - checks for an alphabetic character
 * @c: the character to input
 * Return: 1 if c is alphabetic, 0 otherwise
 */
int _isalpha(int c)
{
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
        return (1);
    else
        return (0);
}

/**
 * myatoi - converts a string to an integer
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
        myoutput = -myresult;
    else
        myoutput = myresult;

    return (myoutput);
}
