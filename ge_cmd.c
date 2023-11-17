#include "shell.h"

/**
 * ge_cmd - function that check file is executable command or not
 * @info: parameter struct
 * @path: path to the file
 *
 * Return: (1) if true, else 0
 */
int ge_cmd(info_t *info, char *path)
{
	struct stat st;

	if (!path || !info)
		return (0);

	if (stat(path, &st) != 0)
	{
		return (0);
	}
	return (S_ISREG(st.st_mode));
}

/**
 * cha_duplicate - function that duplicate characters
 * @strgpath: string path
 * @start: begining of index
 * @end: end of the index
 *
 * Return: string
 */
char *cha_duplicate(char *strgpath, int start, int end)
{
	static char buf[MAX_LENGTH];
	int index = 0, k;

	for (k = start; k < end && index < MAX_LENGTH - 1; k++)
	{
		if (strgpath[k] != ':')
		{
			buf[index] = strgpath[k];
			index++;
		}
	}

	buf[index] = '\0';
	return (buf);
}

/**
 * ge_getpath - function that get path of a command
 * @info: struct parameter
 * @pathstr: string of the command
 * @cmd: command to get the path
 *
 * Return: full path of cmd if found or NULL
 */
char *ge_getpath(info_t *info, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (ge_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = cha_duplicate(pathstr, curr_pos, i);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (ge_cmd(info, path))
				return (path);
			if (!pathstr[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}

