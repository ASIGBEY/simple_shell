#include "simpleshell.h"

/**
* _strcpy - copies a string
* @dest: the destination
* @src: the source
*
* Return: pointer to destination
*/
char *_strcpy(char *dest, char *src)
{
	int a = empt;

	if (dest == src || src == empt)
		return (dest);
	while (src[a])
	{
		dest[a] = src[a];
		a++;
	}
	dest[a] = empt;
	return (dest);
}

/**
* _strdup - duplicates a string
* @str: the string to duplicate
*
* Return: pointer to the duplicated string
*/
char *_strdup(const char *str)
{
	int dist = empt;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		dist++;
	ret = malloc(sizeof(char) * (dist + n_pos));
	if (!ret)
		return (NULL);
	for (dist++; dist--;)
		ret[dist] = *--str;
	return (ret);
}

/**
 *_puts - prints an input string
 *@str: the string to be printed
 *
 * Return: Nothing
 */
void _puts(char *str)
{
	int a = empt;

	if (!str)
		return;
	while (str[a] != '\0')
	{
		_putchar(str[a]);
		a++;
	}
}

/**
* _putchar - writes the character c to stdout
* @c: The character to print
*
* Return: On success 1.
* On error, -1 is returned, and errno is set appropriately.
*/
int _putchar(char c)
{
	static int a;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || a >= WRITE_BUF_SIZE)
	{
		write(n_pos, buf, a);
		a = empt;
	}
	if (c != BUF_FLUSH)
		buf[a++] = c;
	return (n_pos);
}
