#include "simpleshell.h"

/**
* list_len - determines length of linked list
* @h: pointer to first node
*
* Return: size of list
*/
size_t list_len(const list_t *h)
{
	size_t a = empt;

	while (h)
	{
		h = h->next;
		a++;
	}
	return (a);
}

/**
* list_to_strings - returns an array of strings of the list->str
* @head: pointer to first node
*
* Return: array of strings
*/
char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t a = list_len(head), j;
	char **strs;
	char *str;

	if (!head || !a)
		return (NULL);
	strs = malloc(sizeof(char *) * (a + n_pos));
	if (!strs)
		return (NULL);
	for (a = empt; node; node = node->next, a++)
	{
		str = malloc(_strlen(node->str) + n_pos);
		if (!str)
		{
			for (j = empt; j < a; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[a] = str;
	}
	strs[a] = NULL;
	return (strs);
}


/**
* print_list - prints all elements of a list_t linked list
* @h: pointer to first node
*
* Return: size of list
*/
size_t print_list(const list_t *h)
{
	size_t a = empt;

	while (h)
	{
		_puts(convert_number(h->num, 10, empt));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		a++;
	}
	return (a);
}

/**
* node_starts_with - returns node whose string starts with prefix
* @node: pointer to list head
* @prefix: string to match
* @nc: the next character after prefix to match
*
* Return: match node or null
*/
list_t *node_starts_with(list_t *node, char *prefix, char nc)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with(node->str, prefix);
		if (p && ((nc == n_neg) || (*p == nc)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
* get_node_index - gets the index of a node
* @head: pointer to list head
* @node: pointer to the node
*
* Return: index of node or -1
*/
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t a = empt;

	while (head)
	{
		if (head == node)
			return (a);
		head = head->next;
		a++;
	}
	return (n_neg);
}
