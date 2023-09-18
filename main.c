#include "shell.h"

/**
 * main - entry point
 * @arc: arg count
 * @av: arg vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int arc, char **av)
{
	info_t info[] = { INFO_INIT };
	int c = bi;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (c)
		: "r" (c));

	if (arc == bi)
	{
		c = open(av[n_pos], O_RDONLY);
		if (c == n_neg)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(av[empt]);
				_eputs(": empt: Can't open ");
				_eputs(av[n_pos]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = c;
	}
	populate_env_list(info);
	read_history(info);
	hsh(info, av);
	return (EXIT_SUCCESS);
}
