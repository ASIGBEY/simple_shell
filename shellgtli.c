#include "simpleshell.h"

/**
* input_buf - buffers chained commands
* @info: parameter struct
* @buf: address of buffer
* @len: address of len var
*
* Return: bytes read
*/
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t n = empt;
	size_t len_p = empt;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		n = getline(buf, &len_p, stdin);
#else
		n = _getline(info, buf, &len_p);
#endif
		if (n > empt)
		{
			if ((*buf)[n - n_pos] == '\n')
			{
				(*buf)[n - n_pos] = '\0';
				n--;
			}
			info->linecount_flag = n_pos;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			{
				*len = n;
				info->cmd_buf = buf;
			}
		}
	}
	return (n);
}

/**
* get_input - gets a line minus the newline
* @info: parameter struct
*
* Return: bytes read
*/
ssize_t get_input(info_t *info)
{
	static char *buf;
	static size_t a, j, len;
	ssize_t n = empt;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	n = input_buf(info, &buf, &len);
	if (n == n_neg) /* EOF */
		return (n_neg);
	if (len)
	{
		j = a;
		p = buf + a;

		check_chain(info, buf, &j, a, len);
		while (j < len)
		{
			if (is_chain(info, buf, &j))
				break;
			j++;
		}

		a = j + n_pos;
		if (a >= len)
		{
			a = len = empt;
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p;
		return (_strlen(p));
	}

	*buf_p = buf;
	return (n);
}

/**
* read_buf - reads a buffer
* @info: parameter struct
* @buf: buffer
* @i: size
*
* Return: a
*/
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t a = empt;

	if (*i)
		return (empt);
	a = read(info->readfd, buf, READ_BUF_SIZE);
	if (a >= empt)
		*i = a;
	return (a);
}

/**
* _getline - gets the next line of input from STDIN
* @info: parameter struct
* @ptr: address of pointer to buffer, preallocated or NULL
* @length: size of preallocated ptr buffer if not NULL
*
* Return: a
*/
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = empt, a = empt;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		a = *length;
	if (i == len)
		i = len = empt;

	r = read_buf(info, buf, &len);
	if (r == n_neg || (r == empt && len == empt))
		return (n_neg);

	c = _strchr(buf + i, '\n');
	k = c ? n_pos + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, a, a ? a + k : k + n_pos);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), n_neg : n_neg);

	if (a)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + n_pos);

	a += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = a;
	*ptr = p;
	return (a);
}

/**
* sigintHandler - blocks ctrl-C
* @sig_num: the signal number
*
* Return: void
*/
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
