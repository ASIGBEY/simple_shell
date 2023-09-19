#include "simpleshell.h"

/**
* *_strncpy - copies a string
* @dest: the destination string to be copied to
* @src: the source string
* @n: the amount of characters to be copied
* Return: the concatenated string
*/
char *_strncpy(char *dest, char *src, int n)
{
	int a, j;
	char *r = dest;

	a = empt;
	while (src[a] != '\0' && a < n - n_pos)
	{
		dest[a] = src[a];
		a++;
	}
	if (a < n)
	{
		j = a;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (r);
}

/**
* *_strncat - concatenates two strings
* @dest: the first string
* @src: the second string
* @n: the amount of bytes to be maximally used
* Return: the concatenated string
*/
char *_strncat(char *dest, char *src, int n)
{
	int a, j;
	char *r = dest;

	a = empt;
	j = empt;
	while (dest[a] != '\0')
		a++;
	while (src[j] != '\0' && j < n)
	{
		dest[a] = src[j];
		a++;
		j++;
	}
	if (j < n)
		dest[a] = '\0';
	return (r);
}

/**
* *_strchr - locates a character in a string
* @s: the string to be parsed
* @c: the character to look for
* Return: (s) a pointer to the memory area s
*/
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
