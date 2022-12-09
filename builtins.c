#include "main.h"

/**
 * bin_exit - exits the program whit a status
 * @ps: pointer to string
 *
 * Return: nothing
 */
void bin_exit(char **ps)
{
	char *temp;
	char *exit_status;
	char whitespace[] = " \t\n\r\v";
	int i, status;

	temp = strtok(*ps, whitespace);
	temp = strtok(NULL, whitespace);
	if (temp == NULL)
	{
		safe_free(ps);
		exit(0);
	}

	exit_status = temp;
	for (i = 0; exit_status[i] != '\0'; i++)
	{
		if (exit_status[i] < '0' || exit_status[i] > '9')
		{
			fprintf(stderr, "hsh: exit: %s: numeric argument required\n", temp);
			safe_free(ps);
			exit(2);
		}
	}

	temp = strtok(NULL, whitespace);
	if (temp != NULL)
	{
		fprintf(stderr, "hsh: exit: too many arguments\n");
		return;
	}

	printf("exit\n");
	status = atoi(exit_status);
	safe_free(ps);
	exit(status);
}

/**
 * bin_cd - change directory
 * @ps: pointer to string
 *
 * Return: nothing
 */
void bin_cd(char **ps)
{
	char *temp, *leftovers;
	char whitespace[] = " \t\n\r\v";

	temp = strtok(*ps, whitespace);
	temp = strtok(NULL, whitespace);
	if (temp == NULL)
		return;

	leftovers = strtok(NULL, whitespace);
	if (leftovers != NULL)
	{
		fprintf(stderr, "hsh: cd: too many arguments\n");
		return;
	}

	if (chdir(temp) < 0)
	{
		fprintf(stderr, "hsh: cd: %s: No such file or directory\n", temp);
		return;
	}
}
