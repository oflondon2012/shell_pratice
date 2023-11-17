#include "shell.h"
/**
 *ge _environ - function that print current  environment
 * @info: parameter struct
 *
 * Return: Always (0)
 */
int ge_environ(info_t *info)
{
	print_linklist(info->env);
	return (0);
}

/**
 * ge_getenv - function that get environment variable
 * @info: struct parameter
 * @name: environ varriable name
 *
 * Return: environment variable
 */
char *ge_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *par = NULL;

	for (; node != NULL; node = node ->next)
	{
		par = starts_with(node->str, name);
		if (par && *par)
			return (par);
	}
	return (NULL);
}

/**
 * ge_psetenv - function that initialize new environment variable
 *
 * @info: parameter struct
 * Return: Always (0)
 */
int ge_psetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (!ge_setenv(info, info->argv[1], info->argv[2]))
		return (1);
	return (0);
}

/**
 * ge_punsetenv - function that unset environment variable
 * @info: parameter struct
 * Return: Always (0)
 */
int ge_punsetenv(info_t *info)
{
	int k;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (k = 1; k <= info->argc; k++)
		ge_unsetenv(info, info->argv[k]);

	return (0);
}

/**
 * print_envlist - populates env linked list
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int print_envlist(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}

