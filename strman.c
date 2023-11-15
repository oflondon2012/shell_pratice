#include "shell.h"

/**
 * _strcpy - function that copes a string
 * @dest: to the destination
 * @src: from the source
 *
 * Return: pointer to the destination
 */
char *_strcpy(char *dest, char *src)
{
	int j;

	if (dest == src || src == 0)
		return (dest);
	for (j = 0; src[j]; j++)
	{
		dest[j] = src[j];
	}
	dest[j] = 0;
	return (dest);
}

/**
 * _strdup - function that duplicates a string
 * @str: string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *_strdup(const char *str)
{
	int length = 0;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--str;
	return (ret);
}

/**
 * _myputs - function that prints an input string
 * @strg: string to be printed
 *
 * Return: Nothing
 */
void _myputs(char *strg)
{
	int j;

	if (!strg)
		return;
	for (j = 0; strg[j] != '\0'; j++)
	{
		_myputchar(strg[j]);
	}
}

/**
 * _myputchar - function that writes the character to stdout
 * @c: character to be print
 *
 * Return: On success (1), on error (-1)
 */
int _myputchar(char c)
{
	static int k;
	static char buffer[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || k >= WRITE_BUF_SIZE)
	{
		write(1, buffer, k);
		k = 0;
	}
	if (c != BUF_FLUSH)
		buffer[k++] = c;
	return (1);
}

