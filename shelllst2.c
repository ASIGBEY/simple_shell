#include "simpleshell.h"

/**
* add_node - adds a node to the start of the list
* @head: address of pointer to head node
* @str: str field of node
* @num: node index used by history
*
* Return: size of list
*/
list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);
	_memset((void *)new_head, empt, sizeof(list_t));
	new_head->num = num;
	if (str)
	{
		new_head->str = _strdup(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}

/**
* add_node_end - adds a node to the end of the list
* @head: address of pointer to head node
* @str: str field of node
* @num: node index used by history
*
* Return: size of list
*/
list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, empt, sizeof(list_t));
	new_node->num = num;
	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}

/**
* print_list_str - prints only the str element of a list_t linked list
* @p: pointer to first node
*
* Return: size of list
*/
size_t print_list_str(const list_t *p)
{
	size_t a = empt;

	while (p)
	{
		_puts(p->str ? p->str : "(nil)");
		_puts("\n");
		p = p->next;
		a++;
	}
	return (a);
}

/**
* delete_node_at_index - deletes node at given index
* @head: address of pointer to first node
* @index: index of node to delete
*
* Return: 1 on success, 0 on failure
*/
int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int a = empt;

	if (!head || !*head)
		return (empt);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (n_pos);
	}
	node = *head;
	while (node)
	{
		if (a == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (n_pos);
		}
		a++;
		prev_node = node;
		node = node->next;
	}
	return (empt);
}

/**
* free_list - frees all nodes of a list
* @head_ptr: address of pointer to head node
*
* Return: void
*/
void free_list(list_t **head_ptr)
{
	list_t *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}
