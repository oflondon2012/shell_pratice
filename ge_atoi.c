#include "shell.h"

/**
* _atoi - function that convert a string to an integer
* @s: string to be converted
* Return: integer value of the converted string
*/
int _atoi(char *s)
{
	int i = 0, j = 0, k = 0, l = 0, dlent, intval;

	dlent = 0;
	intval  = 0;

	while (s[dlent] != '\0')
		dlent++;
	while (i < dlent && j == 0)
	{
		if (s[i] == '-')
			++l;
		if (s[i] >= '0' && s[i] <= '9')
		{
			intval = s[i] - '0';
			if (l % 2)
				intval = -intval;
			k = k * 10 + intval;
			j = 1;
			if (s[i + 1] < '0' || s[i + 1] > '9')
				break;
			j = 0;
		}
		i++;
	}
	if (j == 0)
		return (0);
	return (k);
}

/**
 * interactive - function that check if shell is in interactive mode
 * @info: parameter address
 *
 * Return: 1 if  interactive mode, else 0
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * _isalpha - function that checks for alphabetic character
 *
 * @c: character to check
 *
 * Return: Always 1 on succes 0 otherwise
 */

int _isalpha(int c)
{
	if ((c >= 65 && c <= 97) || (c >= 97 && c <= 122))
	{
		return (1);
	}

	return (0);
}

/**
 * is_delim - function that check if character is a delimeter
 * @c: char to check
 * @delim: the delimeter string
 * Return: 1 if true, 0 if false
 */
int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

