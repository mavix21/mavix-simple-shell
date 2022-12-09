#include "main.h"

/**
 * free_tree - frees the command tree
 * @cmd: pointer to the tree of type struct cmd
 *
 * Return: nothing
 */
void free_tree(struct cmd *cmd)
{
	struct execcmd *ecmd;
	struct listcmd *lcmd;

	switch (cmd->type)
	{
		case EXEC:
			ecmd = (struct execcmd *)cmd;
			free(ecmd->argv[0]);
			free(ecmd);
			break;

		case LIST:
			lcmd = (struct listcmd *)cmd;
			free_tree(lcmd->left);
			free_tree(lcmd->right);
			free(lcmd);
			break;
	}

	return;
}

/**
 * safe_free - frees the given pointer and sets it to NULL
 * @ps: pointer to the string
 *
 * Return: nothing
 */
void safe_free(char **ps)
{
	if (ps && *ps)
	{
		free(*ps);
		*ps = NULL;
	}
}
