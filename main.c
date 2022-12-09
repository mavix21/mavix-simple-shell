#include "main.h"

/**
 * main - entry point
 *
 * Return: always EXIT_SUCCESS
 */
int main(void)
{
	signal(SIGINT, &handle_sigint);

	/* Buffer that will store the user's input */
	char *line = NULL;
	struct cmd *cmd_tree;

	/* Read and run input commands */
	while (getcmd(&line) >= 0)
	{
		if (isabuiltin(line) == BUILTIN_FAIL)
			continue;

		cmd_tree = parsecmd(line);

		if (cmd_tree == NULL)
			continue;

		if (forking() == 0)
			runcmd(cmd_tree);
		wait(0);
		free_tree(cmd_tree);
	}

	return (EXIT_SUCCESS);
}
