#include "shell.h"

/**
 * initiate_info - function that initializes info_t struct
 * @info: argument
 */
void initiate_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * set_info - function that set information
 * @info: parameter address
 * @av: argument vector
 */
void set_info(info_t *info, char **av)
{
	int j = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t");
		if (!info->argv)
		{

			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (j = 0; info->argv && info->argv[j]; j++)
			;
		info->argc = j;

		alias_replace(info);
		replace_vars(info);
	}
}

/**
 * free_fields - function that frees the structure
 * @info: parameter pointer address
 * @all: to decode if the are all free
 */
void free_fields(info_t *info, int all)
{
	ffree(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buffer)
			free(info->arg);
		if (info->env)
			free_gelist(&(info->env));
		if (info->history)
			free_gelist(&(info->history));
		if (info->alias)
			free_gelist(&(info->alias));
		ffree(info->environ);
		info->environ = NULL;
		bfree((void **)info->cmd_buffer);
		if (info->readfd > 2)
			close(info->readfd);
		_myputchar(BUF_FLUSH);
	}
}

