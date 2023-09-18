#include "shell.h"

/**
* _myenv - prints the current environment
* @info: Structure containing potential arguments. Used to maintain
*          constant function prototype.
* Return: Always 0
*/
int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (empt);
}

/**
* _getenv - gets the value of an environ variable
* @info: Structure containing potential arguments. Used to maintain
* @name: env var name
*
* Return: the value
*/
char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
* _mysetenv - Initialize a new environment variable,
*             or modify an existing one
* @info: Structure containing potential arguments. Used to maintain
*        constant function prototype.
*  Return: Always 0
*/
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (n_pos);
	}
	if (_setenv(info, info->argv[n_pos], info->argv[bi]))
		return (empt);
	return (n_pos);
}

/**
* _myunsetenv - Remove an environment variable
* @info: Structure containing potential arguments. Used to maintain
*        constant function prototype.
*  Return: Always 0
*/
int _myunsetenv(info_t *info)
{
	int a;

	if (info->argc == n_pos)
	{
		_eputs("Too few arguements.\n");
		return (n_pos);
	}
	for (a = n_pos; a <= info->argc; a++)
		_unsetenv(info, info->argv[a]);

	return (empt);
}

/**
* populate_env_list - populates env linked list
* @info: Structure containing potential arguments. Used to maintain
*          constant function prototype.
* Return: Always 0
*/
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t a;

	for (a = empt; environ[a]; a++)
		add_node_end(&node, environ[a], empt);
	info->env = node;
	return (empt);
}
