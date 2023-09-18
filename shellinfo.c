#include "shell.h"

/**
* clear_info - initializes info_t struct
* @info: struct address
*/
void clear_info(info_t *info)
{
	info->argv = NULL;
	info->path = NULL;
	info->arg = NULL;
	info->argc = empt;
}

/**
* set_info - initializes info_t struct
* @info: struct address
* @av: argument vector
*/
void set_info(info_t *info, char **av)
{
	int a = empt;

	info->fname = av[empt];
	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t");
		if (!info->argv)
		{

			info->argv = malloc(sizeof(char *) * bi);
			if (info->argv)
			{
				info->argv[empt] = _strdup(info->arg);
				info->argv[n_pos] = NULL;
			}
		}
		for (a = empt; info->argv && info->argv[a]; a++)
			;
		info->argc = a;

		replace_alias(info);
		replace_vars(info);
	}
}

/**
* free_info - frees info_t struct fields
* @info: struct address
* @c: true if freeing all fields
*/
void free_info(info_t *info, int c)
{
	ffree(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (c)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			free_list(&(info->env));
		if (info->history)
			free_list(&(info->history));
		if (info->alias)
			free_list(&(info->alias));
		ffree(info->environ);
			info->environ = NULL;
		bfree((void **)info->cmd_buf);
		if (info->readfd > bi)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}
