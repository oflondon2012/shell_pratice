#include "shell.h"

/**
 * isschain - function that check current char in buffer is a chain delimeter
 * @par: parameter structure
 * @buf: char buffer
 * @p: address of current position in buffer
 *
 * Return: always (1) on success else 0
 */
int isschain(info_t *par, char *buf, size_t *p)
{
	int chain_type = *p;
	size_t j = *p;

	switch (buf[j])
	{
		case '|':
			if (buf[j + 1] == '|')
				chain_type = CMD_OR;
			break;
		case '&':
			if (buf[j + 1] == '&')
				chain_type = CMD_AND;
			break;
		case ';':
			chain_type = CMD_CHAIN;
			break;
		default:
			return (0);

	}
	buf[j] = '\0';
	*p = ++j;
	par->cmd_buf_type = chain_type;
	return (1);
}

/**
 * check_chain - function that checks if we should continue chaining
 * @info: parameter struct
 * @buf: char buffer
 * @p: address of current position in buffer
 * @i: starting position in buffer
 * @len: length of buffer
 *
 * Return: void
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if ((info->cmd_buf_type == CMD_AND && info->status) ||
			(info->cmd_buf_type == CMD_OR && !info->status))
	{
			buf[i] = '\0';
			j = len;
	}

	*p = j;
}

/**
 * alias_replace - function that replace aliases in the tokenized string
 * @info: parameter struct
 *
 * Return: Always (1) on success else 0
 */
int alias_replace(info_t *info)
{
	int j;
	list_t *node;
	char *p;

	for (j = 0; j < 10; j++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars - function that replaces vars in the tokenized string
 * @info: the parameter struct
 *
 * Return: always (1) on success else 0
 */
int replace_vars(info_t *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (_strcmp(info->argv[i], "$?") == 0)
		{
			replace_string(&(info->argv[i]),
					_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (_strcmp(info->argv[i], "$$") == 0)
		{
			replace_string(&(info->argv[i]),
					_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[i][1], '=');
		if (node)
		{
			replace_string(&(info->argv[i]),
					_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[i], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}

