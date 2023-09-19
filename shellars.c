#include "simpleshell.h"

/**
* is_chain - test if current char in buffer is a chain delimeter
* @info: the parameter struct
* @buf: the char buffer
* @p: address of current position in buf
*
* Return: 1 if chain delimeter, 0 otherwise
*/
int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t c = *p;

	if (buf[c] == '|' && buf[c + n_pos] == '|')
	{
		buf[c] = empt;
		c++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[c] == '&' && buf[c + n_pos] == '&')
	{
		buf[c] = empt;
		c++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[c] == ';')
	{
		buf[c] = empt;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (empt);
	*p = c;
	return (n_pos);
}

/**
* check_chain - checks we should continue chaining based on last status
* @info: the parameter struct
* @buf: the char buffer
* @p: address of current position in buf
* @i: starting position in buf
* @len: length of buf
*
* Return: Void
*/
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t c = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = empt;
			c = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = empt;
			c = len;
		}
	}

	*p = c;
}

/**
* replace_alias - replaces an aliases in the tokenized string
* @info: the parameter struct
*
* Return: 1 if replaced, 0 otherwise
*/
int replace_alias(info_t *info)
{
	int a;
	list_t *node;
	char *p;

	for (a = empt; a < 10; a++)
	{
		node = node_starts_with(info->alias, info->argv[empt], '=');
		if (!node)
			return (empt);
		free(info->argv[empt]);
		p = _strchr(node->str, '=');
		if (!p)
			return (empt);
		p = _strdup(p + n_pos);
		if (!p)
			return (empt);
		info->argv[empt] = p;
	}
	return (n_pos);
}

/**
* replace_vars - replaces vars in the tokenized string
* @info: the parameter struct
*
* Return: 1 if replaced, 0 otherwise
*/
int replace_vars(info_t *info)
{
	int a = empt;
	list_t *node;

	for (a = empt; info->argv[a]; a++)
	{
		if (info->argv[a][empt] != '$' || !info->argv[a][n_pos])
			continue;

		if (!_strcmp(info->argv[a], "$?"))
		{
			replace_string(&(info->argv[a]),
				_strdup(convert_number(info->status, 10, empt)));
			continue;
		}
		if (!_strcmp(info->argv[a], "$$"))
		{
			replace_string(&(info->argv[a]),
				_strdup(convert_number(getpid(), 10, empt)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[a][n_pos], '=');
		if (node)
		{
			replace_string(&(info->argv[a]),
				_strdup(_strchr(node->str, '=') + n_pos));
			continue;
		}
		replace_string(&info->argv[a], _strdup(""));

	}
	return (empt);
}

/**
* replace_string - replaces string
* @old: address of old string
* @new: new string
*
* Return: 1 if replaced, 0 otherwise
*/
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (n_pos);
}
