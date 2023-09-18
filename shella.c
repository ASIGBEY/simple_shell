#include "shell.h"

/**
* interactive - returns true if shell is interactive mode
* @info: struct address
*
* Return: 1 if interactive mode, 0 otherwise
*/
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= bi);
}

/**
* is_delim - checks if character is a delimeter
* @c: the char to check
* @delim: the delimeter string
* Return: 1 if true, 0 if false
*/
int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (n_pos);
	return (empt);
}

/**
*_isalpha - checks for alphabetic character
*@c: The character to input
*Return: 1 if c is alphabetic, 0 otherwise
*/

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (n_pos);
	else
		return (empt);
}

/**
* _atoi - converts a string to an integer
* @s: the string to be converted
* Return: 0 if no numbers in string, converted number otherwise
*/

int _atoi(char *s)
{
	int a, sign = n_pos, flag = empt, pt;
	unsigned int result = empt;

	for (a = empt;  s[a] != '\0' && flag != bi; a++)
	{
		if (s[a] == '-')
			sign *= n_neg;

		if (s[a] >= '0' && s[a] <= '9')
		{
			flag = n_pos;
			result *= 10;
			result += (s[a] - '0');
		}
		else if (flag == n_pos)
			flag = bi;
	}

	if (sign == n_neg)
		pt = -result;
	else
		pt = result;

	return (pt);
}