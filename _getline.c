#include "shell.h"

/**
 * input_buf - function that read input buffer chained command 
 * @info: parameter struct
 * @buffer: address of buffer
 * @len: address of len var
 *
 * Return: bytes read
 */
ssize_t input_buf(info_t *info, char **buffer, size_t *len)
{
	size_t len_p = 0;
	ssize_t byteread = 0;

	if (!*len)
	{
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, sigHandle);
#if USE_GETLINE
		byteread = getline(buffer, &len_p, stdin);
#else
		byteread = _mygetline(info, buffer, &len_p);
#endif
		if (byteread > 0)
		{
			if ((*buffer)[byteread - 1] == '\n')
			{
				(*buffer)[byteread - 1] = '\0'; 
				byteread--;
			}
			info->linecount_flag = 1;
			ge_recomments(*buffer);
			build_history_list(info, *buffer, info->counthist++);
			
			*len = byteread;
			info->cmd_buffer = buffer;
		}
	}
	return (byteread);
}

/**
 * get_input - gets a line minus the newline
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_input(info_t *info)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	_myputchar(BUF_FLUSH);
	r = input_buf(info, &buf, &len);
	if (r == -1) /* EOF */
		return (-1);
	if (len)	/* we have commands left in the chain buffer */
	{
		j = i; /* init new iterator to current buf position */
		p = buf + i; /* get pointer for return */

		check_chain(info, buf, &j, i, len);
		while (j < len) /* iterate to semicolon or end */
		{
			if (isschain(info, buf, &j))
				break;
			j++;
		}

		i = j + 1; /* increment past nulled ';'' */
		if (i >= len) /* reached end of buffer? */
		{
			i = len = 0; /* reset position and length */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /* pass back pointer to current command position */
		return (_strlen(p)); /* return length of current command */
	}

	*buf_p = buf; /* else not a chain, pass back buffer from _getline() */
	return (r); /* return length of buffer from _getline() */
}

/**
 * read_buf - reads a buffer
 * @info: parameter struct
 * @buf: buffer
 * @i: size
 *
 * Return: r
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(info->readfd, buf, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * _mygetline - gets the next line of input from STDIN
 * @param: parameter struct
 * @addr: address of pointer to buffer, preallocated or NULL
 * @presize: size of preallocated ptr buffer if not NULL
 *
 * Return: size
 */
int _mygetline(info_t *param, char **addr, size_t *presize)
{
	static char buffer[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t byteread = 0, size = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *addr;
	if (p && presize)
		size = *presize;
	if (i == len)
		i = len = 0;

	byteread = read_buf(param, buffer, &len);
	if (byteread == -1 || (byteread == 0 && len == 0))
		return (-1);

	c = _strchr(buffer + i, '\n');
	k = c ? 1 + (unsigned int)(c - buffer) : len;
	new_p = _realloc(p, size, size ? size + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (size)
		_strncat(new_p, buffer + i, k - i);
	else
		_strncpy(new_p, buffer + i, k - i + 1);

	size += k - i;
	i = k;
	p = new_p;

	if (presize)
		*presize = size;
	*addr = p;
	return (size);
}

/**
 * sigHandle - function that disable ctrl-C
 * @sig_number: signal number
 *
 * Return: void
 */
void sigHandle(__attribute__((unused))int sig_number)
{
	_myputs("\n");
	_myputs("$ ");
	_myputchar(BUF_FLUSH);
}

