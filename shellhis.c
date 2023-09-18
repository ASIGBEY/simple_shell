#include "shell.h"

/**
* get_history_file - gets the history file
* @info: parameter struct
*
* Return: allocated string containg history file
*/

char *get_history_file(info_t *info)
{
	char *buf, *dir;

	dir = _getenv(info, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + bi));
	if (!buf)
		return (NULL);
	buf[empt] = empt;
	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return (buf);
}

/**
* write_history - creates a file, or appends to an existing file
* @info: the parameter struct
*
* Return: 1 on success, else -1
*/
int write_history(info_t *info)
{
	ssize_t fd;
	char *filename = get_history_file(info);
	list_t *node = NULL;

	if (!filename)
		return (n_neg);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == n_neg)
		return (n_neg);
	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (n_pos);
}

/**
* read_history - reads history from file
* @info: the parameter struct
*
* Return: histcount on success, 0 otherwise
*/
int read_history(info_t *info)
{
	int a, last = empt, linecount = empt;
	ssize_t fd, rdlen, fsize = empt;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(info);

	if (!filename)
		return (empt);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == n_neg)
		return (empt);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < bi)
		return (empt);
	buf = malloc(sizeof(char) * (fsize + n_pos));
	if (!buf)
		return (empt);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = empt;
	if (rdlen <= empt)
		return (free(buf), empt);
	close(fd);
	for (a = empt; a < fsize; a++)
		if (buf[a] == '\n')
		{
			buf[a] = empt;
			build_history_list(info, buf + last, linecount++);
			last = a + n_pos;
		}
	if (last != a)
		build_history_list(info, buf + last, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), empt);
	renumber_history(info);
	return (info->histcount);
}

/**
* build_history_list - adds entry to a history linked list
* @info: Structure containing potential arguments. Used to maintain
* @buf: buffer
* @linecount: the history linecount, histcount
*
* Return: Always 0
*/
int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (empt);
}

/**
* renumber_history - renumbers the history linked list after changes
* @info: Structure containing potential arguments. Used to maintain
*
* Return: the new histcount
*/
int renumber_history(info_t *info)
{
	list_t *node = info->history;
	int a = empt;

	while (node)
	{
		node->num = a++;
		node = node->next;
	}
	return (info->histcount = a);
}
