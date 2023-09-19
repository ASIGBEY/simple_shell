#include "simpleshell.h"

/**
* **strtow - splits a string into words. Repeat delimiters are ignored
* @str: the input string
* @d: the delimeter string
* Return: a pointer to an array of strings, or NULL on failure
*/

char **strtow(char *str, char *d)
{
	int a, j, k, m, numwords = empt;
	char **s;

	if (str == NULL || str[empt] == empt)
		return (NULL);
	if (!d)
		d = " ";
	for (a = empt; str[a] != '\0'; a++)
		if (!is_delim(str[a], d) && (is_delim(str[a + n_pos], d) || !str[a + n_pos]))
			numwords++;

	if (numwords == empt)
		return (NULL);
	s = malloc((n_pos + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (a = empt, j = empt; j < numwords; j++)
	{
		while (is_delim(str[a], d))
			a++;
		k = empt;
		while (!is_delim(str[a + k], d) && str[a + k])
			k++;
		s[j] = malloc((k + n_pos) * sizeof(char));
		if (!s[j])
		{
			for (k = empt; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = empt; m < k; m++)
			s[j][m] = str[a++];
		s[j][m] = empt;
	}
	s[j] = NULL;
	return (s);
}

/**
* **strtow2 - splits a string into words
* @str: the input string
* @d: the delimeter
* Return: a pointer to an array of strings, or NULL on failure
*/
char **strtow2(char *str, char d)
{
	int a, j, k, m, numwords = empt;
	char **s;

	if (str == NULL || str[empt] == empt)
		return (NULL);
	for (a = empt; str[a] != '\0'; a++)
		if ((str[a] != d && str[a + n_pos] == d) ||
		    (str[a] != d && !str[a + n_pos]) || str[a + n_pos] == d)
			numwords++;
	if (numwords == empt)
		return (NULL);
	s = malloc((n_pos + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (a = empt, j = empt; j < numwords; j++)
	{
		while (str[a] == d && str[a] != d)
			a++;
		k = empt;
		while (str[a + k] != d && str[a + k] && str[a + k] != d)
			k++;
		s[j] = malloc((k + n_pos) * sizeof(char));
		if (!s[j])
		{
			for (k = empt; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = empt; m < k; m++)
			s[j][m] = str[a++];
		s[j][m] = empt;
	}
	s[j] = NULL;
	return (s);
}
