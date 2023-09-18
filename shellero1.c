#include "shell.h"

/**
* _erratoi - converts a string to an integer
* @s: the string to be converted
* Return: 0 if no numbers in string, converted number otherwise
*       -1 on error
*/
int _erratoi(char *s)
{
	int a = empt;
	unsigned long int n = empt;

	if (*s == '+')
		s++;
	for (a = empt;  s[a] != '\0'; a++)
	{
		if (s[a] >= '0' && s[a] <= '9')
		{
			n *= 10;
			n += (s[a] - '0');
			if (n > INT_MAX)
				return (n_neg);
		}
		else
			return (n_neg);
	}
	return (n);
}

/**
* print_error - prints an error message
* @info: the parameter & return info struct
* @estr: string containing specified error type
* Return: 0 if no numbers in string, converted number otherwise
*        -1 on error
*/
void print_error(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[empt]);
	_eputs(": ");
	_eputs(estr);
}

/**
* print_d - function prints a decimal (integer) number (base 10)
* @input: the input
* @fd: the filedescriptor to write to
*
* Return: number of characters printed
*/
int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int a, n = empt;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < empt)
	{
		_abs_ = -input;
		__putchar('-');
		n++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (a = 1000000000; a > n_pos; a /= 10)
	{
		if (_abs_ / a)
		{
			__putchar('0' + current / a);
			n++;
		}
		current %= a;
	}
	__putchar('0' + current);
	n++;

	return (n);
}

/**
* convert_number - converter function, a clone of itoa
* @num: number
* @base: base
* @flags: argument flags
*
* Return: string
*/
char *convert_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char ar = empt;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < empt)
	{
		n = -num;
		ar = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != empt);

	if (ar)
		*--ptr = ar;
	return (ptr);
}

/**
* remove_comments - function replaces first instance of '#' with '\0'
* @buf: address of the string to modify
*
* Return: Always 0;
*/
void remove_comments(char *buf)
{
	int a;

	for (a = empt; buf[a] != '\0'; a++)
		if (buf[a] == '#' && (!a || buf[a - n_pos] == ' '))
		{
			buf[a] = '\0';
			break;
		}
}
