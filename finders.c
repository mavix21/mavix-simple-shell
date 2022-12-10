#include "main.h"

/**
 * cmdfinder - looks for a given file in the current PATH
 * @command: command to look for
 *
 * Return: if access is posible, return the absolute path
 * where the command was found. NULL otherwise
 */
char *cmdfinder(char *line)
{
	char *path = getenv("PATH"), *temp = NULL;
	char paths[512];
	char *dir = NULL, *command, *token;

	if (path == NULL)
	{
		fprintf(stderr, "Error: PATH environment variable not set\n");
		return (NULL);
	}

	token = strtok(line, " \t\n\r\v;");
	if (token == NULL)
		return (NULL);

	command = strdup(token);
	if (access(command, F_OK) != -1)
		return (command);

	temp = strdup(path);
	dir = strtok(temp, ":");
	while (dir != NULL)
	{
		snprintf(paths, sizeof(paths), "%s/%s", dir, command);
		if (access(paths, F_OK) != -1)
		{
			safe_free(&command);
			command = strdup(paths);
			safe_free(&temp);
			return (command);
		}
		memset(paths, 0, sizeof(paths));
		dir = strtok(NULL, ":");
	}
	fprintf(stderr, "hsh: %s: command not found\n", command);
	safe_free(&command);
	safe_free(&temp);
	return (NULL);
}

/**
 * isabuiltin - checks if the first argument is a builtin
 * @line: string containing user's input
 *
 * Return: does not return on success. On failure, returns 1
 * if first argument is not a builtin, returns 2 if argument is
 * a builtin but falied to execute
 */
int isabuiltin(char *line)
{
	builtin_t bins[] = {
		{"exit", bin_exit},
		{"cd", bin_cd},
		/**
		 * {"env", bin_env},
		 * {"setenv", bin_setenv},
		 * {"unsetenv", bin_unsetenv},
		 */
		{NULL, NULL}
	};
	int i;
	char *temp, *dummy;

	dummy = strdup(line);
	temp = strtok(dummy, " \t\n\v\r");
	if (temp == NULL)
	{
		safe_free(&dummy);
		return (1);
	}

	for (i = 0; bins[i].builtin != NULL; i++)
	{
		if (!strcmp(temp, bins[i].builtin))
		{
			safe_free(&dummy);
			bins[i].f(&line);
			return (BUILTIN_FAIL);
		}
	}
	if (dummy != NULL)
		safe_free(&dummy);

	return (1);
}

/**
 * peek - checks if the first non whitespace character
 * matches any token
 * @ps: pointer to string
 * @es: end of string
 * @tokens: string of tokens
 *
 * Return: 1 if matches, 0 otherwise
 */
int peek(char **ps, char *es, char *tokens)
{
	char *s;

	s = *ps;
	while (s < es && strchr(" \t\r\v", *s))
		s++;
	*ps = s;
	return (*s && strchr(tokens, *s));	
}
