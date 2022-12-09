#include "main.h"

/**
 * parsecmd - builds the command tree by calling the corresponding
 * parser functions
 * @line: user's input string
 *
 * Return: pointer to command tree
 */
struct cmd *parsecmd(char *line)
{
	char *es;
	struct cmd *cmd;

	cmd = parseexec(&line);
	return (cmd);
}

/**
 * parseexec - builds a node of type struct execcmd
 * @ps: pointer to string
 *
 * Return: pointer to node of type struct cmd
 */
struct cmd *parseexec(char **ps)
{
	int argc = 0;
	char *token, *command, *dummy;
	char *whitespace = " \t\r\n\v";
	struct execcmd *cmd;
	struct cmd *ret;

	dummy = strdup(*ps);
	token = strtok(dummy, whitespace);
	if (token == NULL)
	{
		safe_free(&dummy);
		return (NULL);
	}
	command = strdup(token);
	safe_free(&dummy);

	/* This must be a valid command, so we search for it in the PATH */
	command = cmdfinder(command);
	if (command == NULL)
		return (NULL);

	ret = execcmd();
	cmd = (struct execcmd *)ret;
	cmd->argv[argc++] = command;
	token = strtok(*ps, whitespace);
	token = strtok(NULL, whitespace);
	while (token != NULL)
	{
		cmd->argv[argc++] = token;
		token = strtok(NULL, whitespace);
	}
	cmd->argv[argc] = NULL;
	return (ret);
}
