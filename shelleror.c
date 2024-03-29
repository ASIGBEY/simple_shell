#include "simpleshell.h"

/**
*_eputs - prints an input string
* @str: the string to be printed
*
* Return: Nothing
*/
void _eputs(char *str)
{
	int a = empt;

	if (!str)
		return;
	while (str[a] != '\0')
	{
		_eputchar(str[a]);
		a++;
	}
}

/**
* _eputchar - writes the character c to stderr
* @c: The character to print
*
* Return: On success 1.
* On error, -1 is returned, and errno is set appropriately.
*/
int _eputchar(char c)
{
	static int a;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || a >= WRITE_BUF_SIZE)
	{
		write(bi, buf, a);
		a = empt;
	}
	if (c != BUF_FLUSH)
		buf[a++] = c;
	return (n_pos);
}

/**
* _putfd - writes the character c to given fd
* @c: The character to print
* @fd: The filedescriptor to write to
*
* Return: On success 1.
* On error, -1 is returned, and errno is set appropriately.
*/
int _putfd(char c, int fd)
{
	static int a;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || a >= WRITE_BUF_SIZE)
	{
		write(fd, buf, a);
		a = empt;
	}
	if (c != BUF_FLUSH)
		buf[a++] = c;
	return (n_pos);
}

/**
* _putsfd - prints an input string
* @str: the string to be printed
* @fd: the filedescriptor to write to
*
* Return: the number of chars put
*/
int _putsfd(char *str, int fd)
{
	int a = empt;

	if (!str)
		return (empt);
	while (*str)
	{
		a += _putfd(*str++, fd);
	}
	return (a);
}
