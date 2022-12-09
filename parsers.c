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
	struct cmd *cmd;
	char *es, *anchor, *dummy;

	anchor = line;
	es = line + strlen(line);
	cmd = parseline(&line, es);
	line = anchor;
	dummy = strtok(line, " \t\n\r\v;");
	while (dummy != NULL)
		dummy = strtok(NULL, " \t\n\r\v;");
	return (cmd);
}

/**
 * parseexec - builds a node of type struct execcmd
 * @ps: pointer to string
 *
 * Return: pointer to node of type struct cmd, NULL if first
 * token is not a valid command
 */
struct cmd *parseline(char **ps, char *es)
{
	struct cmd *cmd;

	cmd = parseexec(ps, es);
	if (peek(ps, es, ";\n"))
	{
		gettoken(ps, es, 0);
		cmd = listcmd(cmd, parseline(ps, es));
	}
	return cmd;
}

/**
 * parseexec - builds a node of type struct execcmd
 * @ps: pointer to string
 * @es: end of string
 *
 * Return: pointer to node of type struct cmd, NULL if first
 * token is not a valid command
 */
struct cmd *parseexec(char **ps, char *es)
{
	int argc = 0, token;
	char *command, *dummy, *q, *s;
	char *whitespace = " \t\r\v";
	struct execcmd *cmd;
	struct cmd *ret;

	dummy = strdup(*ps);
	command = cmdfinder(dummy);
	safe_free(&dummy);
	if (command == NULL)
		return (NULL);

	ret = execcmd();
	cmd = (struct execcmd *)ret;
	cmd->argv[argc++] = command;
	s = *ps;
	while (s < es && strchr(whitespace, *s))
		s++;
	while (s < es && !strchr(whitespace, *s) && !strchr(";\n", *s))
		s++;
	while (!peek(&s, es, ";\n"))
	{
		if ((token = gettoken(&s, es, &q)) == 0)
			break;
		cmd->argv[argc++] = q;
	}
	cmd->argv[argc] = NULL;
	*ps = s;
	return (ret);
}
