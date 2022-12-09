#include "main.h"

/**
 * execcmd - allocates memory for a structure of type struct execcmd
 *
 * Return: pointer to structure of type struct cmd
 */
struct cmd *execcmd(void)
{
	struct execcmd *cmd;

	cmd = malloc(sizeof(*cmd));
	memset(cmd, 0, sizeof(*cmd));
	cmd->type = EXEC;

	return ((struct cmd *)cmd);
}

/**
 * listcmd - allocates memory for a structure of type struct listcmd
 * @left: pointer to a command tree which be executed first
 * @right: pointer to a command tree which be executed second
 *
 * Return: pointer to structure of type struct cmd
 */
struct cmd *listcmd(struct cmd *left, struct cmd *right)
{
	struct listcmd *cmd;

	cmd = malloc(sizeof(*cmd));
	memset(cmd, 0, sizeof(*cmd));
	cmd->type = LIST;
	cmd->left = left;
	cmd->right = right;

	return ((struct cmd *)cmd);
}
