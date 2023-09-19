#include "simpleshell.h"

/**
* _myexit - exits the shell
* @info: Structure containing potential arguments. Used to maintain
*          constant function prototype.
*  Return: exits with a given exit status
*         (0) if info.argv[0] != "exit"
*/
int _myexit(info_t *info)
{
	int out;

	if (info->argv[n_pos])
	{
		out = _erratoi(info->argv[n_pos]);
		if (out == n_neg)
		{
			info->status = bi;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[n_pos]);
			_eputchar('\n');
			return (n_pos);
		}
		info->err_num = _erratoi(info->argv[n_pos]);
		return (nbi);
	}
	info->err_num = n_neg;
	return (nbi);
}

/**
* _mycd - changes the current directory of the process
* @info: Structure containing potential arguments. Used to maintain
*          constant function prototype.
*  Return: Always 0
*/
int _mycd(info_t *info)
{
	char *a, *dir, buffer[1024];
	int chdir_ret;

	a = getcwd(buffer, 1024);
	if (!a)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[n_pos])
	{
		dir = _getenv(info, "HOME=");
		if (!dir)
			chdir_ret =
				chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp(info->argv[n_pos], "-") == empt)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(a);
			_putchar('\n');
			return (n_pos);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chdir_ret =
			chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[n_pos]);
	if (chdir_ret == n_neg)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[n_pos]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (empt);
}

/**
* _myhelp - changes the current directory of the process
* @info: Structure containing potential arguments. Used to maintain
*          constant function prototype.
*  Return: Always 0
*/
int _myhelp(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (empt)
		_puts(*arg_array);
	return (empt);
}
