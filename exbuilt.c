#include "shell.h"

/**
 * _myhistory - Function that displays the history list
 *
 * @info: parameter
 * Return: Always (0)
 */
int _myhistory(info_t *info)
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
	char *p, c;
	int ret;

	p = _strchr(strg, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delete_node_at_index(&(info->alias),
			get_node_index(info->alias, node_starts_with(info->alias, strg, -1)));
	*p = c;
	return (ret);
}

/**
 * set_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(info_t *info, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
			_myputchar(*a);
		_myputchar('\'');
		_myputs(p + 1);
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

