#include "simpleshell.h"

/**
* get_environ - returns the string array copy of our environ
* @info: Structure containing potential arguments. Used to maintain
*          constant function prototype.
* Return: Always 0
*/
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = empt;
	}

	return (info->environ);
}

/**
* _unsetenv - Remove an environment variable
* @info: Structure containing potential arguments. Used to maintain
*        constant function prototype.
*  Return: 1 on delete, 0 otherwise
* @var: the string env var property
*/
int _unsetenv(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t a = empt;
	char *p;

	if (!var || !node)
		return (empt);

	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), a);
			a = empt;
			node = info->env;
			continue;
		}
		node = node->next;
		a++;
	}
	return (info->env_changed);
}

/**
* _setenv - Initialize a new environment variable,
*             or modify an existing one
* @info: Structure containing potential arguments. Used to maintain
*        constant function prototype.
* @var: the string env var property
* @value: the string env var value
*  Return: Always 0
*/
int _setenv(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (empt);

	buf = malloc(_strlen(var) + _strlen(value) + bi);
	if (!buf)
		return (n_pos);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = info->env;
	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = n_pos;
			return (empt);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buf, empt);
	free(buf);
	info->env_changed = n_pos;
	return (empt);
}
