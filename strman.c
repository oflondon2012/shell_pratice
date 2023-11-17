#include "shell.h"

/**
 * _strcpy - function that copies string pointed to by src
 * @dest: destination to copy from
 * @src: where to copy to
 *
 * Return: string value
 */
char *_strcpy(char *dest, char *src)
{
	int j = 0, k = 0;

	while (*(src + j ) != '\0')
		j++;
	for (k = 0; k < j; k++)
	{
		dest[k] = src[k];
	}
	dest[j] = '\0';
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

