#include "shell.h"

/**
* _myhistory - displays the history list, one command by line, preceded
*              with line numbers, starting at 0.
* @info: Structure containing potential arguments. Used to maintain
*        constant function prototype.
*  Return: Always 0
*/
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (empt);
}

/**
* unset_alias - sets alias to string
* @info: parameter struct
* @str: the string alias
*
* Return: Always 0 on success, 1 on error
*/
int unset_alias(info_t *info, char *str)
{
	char *p, d;
	int t;

	p = _strchr(str, '=');
	if (!p)
		return (n_pos);
	d = *p;
	*p = empt;
	t = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, n_neg)));
	*p = d;
	return (t);
}

/**
* set_alias - sets alias to string
* @info: parameter struct
* @str: the string alias
*
* Return: Always 0 on success, 1 on error
*/
int set_alias(info_t *info, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (n_pos);
	if (!*++p)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, empt) == NULL);
}

/**
* print_alias - prints an alias string
* @node: the alias node
*
* Return: Always 0 on success, 1 on error
*/
int print_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(p + n_pos);
		_puts("'\n");
		return (empt);
	}
	return (n_pos);
}

/**
* _myalias - mimics the alias builtin (man alias)
* @info: Structure containing potential arguments. Used to maintain
*          constant function prototype.
*  Return: Always 0
*/
int _myalias(info_t *info)
{
	int n = empt;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == n_pos)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (empt);
	}
	for (n = n_pos; info->argv[n]; n++)
	{
		p = _strchr(info->argv[n], '=');
		if (p)
			set_alias(info, info->argv[n]);
		else
			print_alias(node_starts_with(info->alias, info->argv[n], '='));
	}

	return (empt);
}
