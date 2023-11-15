#include "shell.h"

/**
 * ge_erratoi - convert a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 * -1 on error
 */
int ge_erratoi(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;  /* TODO: why does this make main return 255? */
	for (i = 0;  s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_errors - prints an error message
 * @info: the parameter & return info struct
 * @estr: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 * -1 on error
 */
void print_errors(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_fdd(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * print_fdd - function that prints a decimal (integer) number (base 10)
 * @input: input value
 * @fd: the file descriptor
 *
 * Return: number of characters print out
 */
int print_fdd(int input, int fd)
{
	int (*__myputchar)(char) = _myputchar;
	int count = 0, divs, digt;
	unsigned int _abs_ = (input < 0) ? -input : input;

	if (fd == STDERR_FILENO)
		__myputchar = _eputchar;
	if (input < 0)
	{
		__myputchar('-');
		count++;
	}
	for (divs = 1000000000; divs > 1; divs /= 10)
	{
		digt = _abs_ / divs;
		if (digt || divs == 1)
		{
			__myputchar('0' + digt);
			count++;
		}
		_abs_ %= divs;
	}

	return (count);
}

/**
 * convert_number - function that convert number
 * @num: number to convert
 * @base: base to convert to
 * @flags: the argument flags
 *
 * Return: string
 */
char *convert_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char *ptr = &buffer[sizeof(buffer) - 1];
	unsigned long n;


	*ptr = '\0';
	n = (num < 0 && !(flags & CONVERT_UNSIGNED)) ? -num : num;
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (num < 0 && !(flags & CONVERT_UNSIGNED))
		*--ptr = '-';
	return (ptr);
}


/**
 * ge_recomments - function that replaces first instance of '#' with '\0'
 * @buffer: addriss of the string
 *
 * Return: Always 0;
 */
void ge_recomments(char *buffer)
{
	int j = 0;

	while (buffer[j] != '\0')
	{
		if (buffer[j] == '#' && (!j || buffer[j - 1] == ' '))
		{
			buffer[j] = '\0';
			break;
		}
		j++;
	}
}

