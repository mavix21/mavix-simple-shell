#include "main.h"

/**
 * forking - forks the current process
 *
 * Return: the corresponding process pid
 */
pid_t forking(void)
{
	pid_t my_pid;

	my_pid = fork();
	if (my_pid == -1)
	{
		perror("Error: ");
		exit(1);
	}

	return (my_pid);
}

/**
 * handle_sigint - handles the SIGINT signal
 * @sig_num: signal to be handled (SIGINT in this case)
 *
 * Return: nothing
 */
void handle_sigint(int sig_num)
{
	signal(SIGINT, &handle_sigint);
	write(1, "\n$ ", 3);
}
