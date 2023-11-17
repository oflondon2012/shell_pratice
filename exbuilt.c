#include "shell.h"

/**
 * ge_history - Function that displays the history list
 *
 * @info: parameter
 * Return: Always (0)
 */
int ge_history(info_t *info)
{
	print_lists(info->history);
	return (0);
}

/**
 * unset_alias - function that set alias to string
 * @info: parameter struct
 * @strg: the string alias
 *
 * Return: Always (0) when successful else 1
 */
int unset_alias(info_t *info, char *strg)
{
	char *position, save_car;
	int delalias;

	position = _strchr(strg, '=');
	if (!position)
		return (1);
	save_car = *position;
	*position = '\0';
	delalias = delete_node_at_index(&(info->alias),
			get_node_index(info->alias, node_starts_with(info->alias, strg, -1)));
	*position = save_car;
	return (delalias);
}

/**
 * set_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(info_t *info, char *strg)
{
	char *position;

	position = _strchr(strg, '=');
	if (!position)
		return (1);
	if (!*++position)
		return (unset_alias(info, strg));

	unset_alias(info, strg);
	return (add_node_end(&(info->alias), strg, 0) == NULL);
}

/**
 * print_alias - function that prints an alias string
 * @node: alias node
 *
 * Return: Always (0) when successful,else 1
 */
int print_alias(list_t *node)
{
	char *position = NULL, *alias = NULL;

	if (node)
	{
		position = _strchr(node->str, '=');
		for (alias = node->str; alias <= position; alias++)
			_myputchar(*alias);
		_myputchar('\'');
		_myputs(position + 1);
		_myputs("'\n");
		return (0);
	}
	return (1);
}

/**
 *ge _alias - function that mimic the alias builtin (man alias)
 * @info: parameter pointer 
 * Return: Always (0)
 */
int ge_alias(info_t *info)
{
	int k = 0;
	char *par = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (k = 1; info->argv[k]; k++)
	{
		par = _strchr(info->argv[k], '=');
		if (par)
			set_alias(info, info->argv[k]);
		else
			print_alias(node_starts_with(info->alias, info->argv[k], '='));
	}

	return (0);
}

