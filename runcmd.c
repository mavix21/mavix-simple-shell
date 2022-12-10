#include "main.h"

/**
 * runcmd - executes the command tree
 * @cmd: command tree
 *
 * Return: nothing
 */
void runcmd(struct cmd *cmd)
{
	struct execcmd *ecmd;
	struct listcmd *lcmd;
	char *strerr;

	if (cmd == NULL)
		exit(1);

	switch (cmd->type)
	{
		case EXEC:
			ecmd = (struct execcmd *)cmd;
			if (ecmd->argv[0] == 0)
				exit(1);
			execve(ecmd->argv[0], ecmd->argv, NULL);
			strerr = strrchr(ecmd->argv[0], '/');
			strerr++;
			fprintf(stderr, "hsh: %s: ", strerr);
			perror(0);
			break;

		case LIST:
			lcmd = (struct listcmd *)cmd;
			if (forking() == 0)
				runcmd(lcmd->left);
			wait(0);
			runcmd(lcmd->right);
			break;
	}

	exit(0);
}
