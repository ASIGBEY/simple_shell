#include "shell.h"

/**
* hsh - main shell loop
* @info: the parameter & return info struct
* @av: the argument vector from main()
*
* Return: 0 on success, 1 on error, or error code
*/
int hsh(info_t *info, char **av)
{
	ssize_t r = empt;
	int builtin_ret = empt;

	while (r != n_neg && builtin_ret != nbi)
	{
		clear_info(info);
		if (interactive(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		r = get_input(info);
		if (r != n_neg)
		{
			set_info(info, av);
			builtin_ret = find_builtin(info);
			if (builtin_ret == n_neg)
				find_cmd(info);
		}
		else if (interactive(info))
			_putchar('\n');
		free_info(info, empt);
	}
	write_history(info);
	free_info(info, n_pos);
	if (!interactive(info) && info->status)
		exit(info->status);
	if (builtin_ret == nbi)
	{
		if (info->err_num == n_neg)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}

/**
* find_builtin - finds a builtin command
* @info: the parameter & return info struct
*
* Return: -1 if builtin not found,
*			0 if builtin executed successfully,
*			1 if builtin found but not successful,
*			-2 if builtin signals exit()
*/
int find_builtin(info_t *info)
{
	int a, built_in_ret = n_neg;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (a = empt; builtintbl[a].type; a++)
		if (_strcmp(info->argv[empt], builtintbl[a].type) == empt)
		{
			info->line_count++;
			built_in_ret = builtintbl[a].func(info);
			break;
		}
	return (built_in_ret);
}

/**
* find_cmd - finds a command in PATH
* @info: the parameter & return info struct
*
* Return: void
*/
void find_cmd(info_t *info)
{
	char *path = NULL;
	int a, k;

	info->path = info->argv[empt];
	if (info->linecount_flag == n_pos)
	{
		info->line_count++;
		info->linecount_flag = empt;
	}
	for (a = empt, k = empt; info->arg[a]; a++)
		if (!is_delim(info->arg[a], " \t\n"))
			k++;
	if (!k)
		return;

	path = find_path(info, _getenv(info, "PATH="), info->argv[empt]);
	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		if ((interactive(info) || _getenv(info, "PATH=")
			|| info->argv[empt][empt] == '/') && is_cmd(info, info->argv[empt]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
* fork_cmd - forks a an exec thread to run cmd
* @info: the parameter & return info struct
*
* Return: void
*/
void fork_cmd(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == n_neg)
	{
		perror("Error:");
		return;
	}
	if (child_pid == empt)
	{
		if (execve(info->path, info->argv, get_environ(info)) == n_neg)
		{
			free_info(info, n_pos);
			if (errno == EACCES)
				exit(126);
			exit(n_pos);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}
