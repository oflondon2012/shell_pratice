#include "shell.h"

/**
 * *_strncpy - function that copies the string pointed to by srs
 * @dest: destination string
 * @src: where to copy from
 * @num: the amount of character to be copied
 * Return: the concatenated string
 */
char *_strncpy(char *dest, char *src, int num)
{
	int i = 0, j;
	char *s = dest;

	while (src[i] != '\0' && i < num - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < num)
	{
		j = i;
		while (j < num)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 * *_strncat - function that concatenat two strings
 * @dest: first string
 * @src: second string
 * @num: amount of bytes to be used
 * Return: concatenated string
 */
char *_strncat(char *dest, char *src, int num)
{
	int i, j;
	char *s = dest;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < num)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < num)
		dest[i] = '\0';
	return (s);
}

/**
 * *_strchr - function that locate(s) a character in a string
 * @s: string to parse
 * @c: character to look for
 * Return: pointer to the memory area
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}

