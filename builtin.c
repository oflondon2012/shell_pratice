#include "shell.h"

/**
 * ge_myexit - function that exitss the shell
 * @info: parameter
 *
 * Return: (0) if info.argv[0] != "exit"
 */
int ge_myexit(info_t *info)
{
	int echeck;

	if (info->argv[1])
	{
		echeck = ge_erratoi(info->argv[1]);
		if (echeck == -1)
		{
			info->status = 2;
			print_errors(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = echeck;
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * ge_mycd - function that change the current directory of the process
 * @info: argument
 * Return: Always (0) 
 */
int ge_mycd(info_t *info)
{
	char *dir, buffer[1024], *cu_dir;
	int chdir_ret;

	cu_dir = getcwd(buffer, 1024);
	if (!cu_dir)
		_myputs("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = ge_getenv(info, "HOME=");
		if (!dir)
			chdir_ret = /* SHUT: just to shut this */
				chdir((dir = ge_getenv(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!ge_getenv(info, "OLDPWD="))
		{
			_myputs(cu_dir);
			_myputchar('\n');
			return (1);
		}
		_myputs(ge_getenv(info, "OLDPWD=")), _myputchar('\n');
		chdir_ret = /* SHUT: TO shut the code */
			chdir((dir = ge_getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		print_errors(info, "can't cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		ge_setenv(info, "OLDPWD", ge_getenv(info, "PWD="));
		ge_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * ge_myhelp - function that handle help command
 * @info: argument
 *
 * Return: Always (0)
 */
int ge_myhelp(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_myputs("Implement the help function. Trying to gather information about it \n");
	if (0)
		_myputs(*arg_array); /* temp att_unused workaround */
	return (0);
}

