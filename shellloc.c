#include "simpleshell.h"

/**
* *_memset - fills memory with a constant byte
* @p: the pointer to the memory area
* @b: the byte to fill *s with
* @n: the amount of bytes to be filled
* Return: (s) a pointer to the memory area s
*/
char *_memset(char *p, char b, unsigned int n)
{
	unsigned int a;

	for (a = empt; a < n; a++)
		p[a] = b;
	return (p);
}

/**
* ffree - frees a string of strings
* @pp: string of strings
*/
void ffree(char **pp)
{
	char **s = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(s);
}

/**
* _realloc - reallocates a block of memory
* @ptr: pointer to previous malloc'ated block
* @old_size: byte size of previous block
* @new_size: byte size of new block
*
* Return: pointer to da ol'block nameen.
*/
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *r;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	r = malloc(new_size);
	if (!r)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		r[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (r);
}
