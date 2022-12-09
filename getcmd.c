#include "main.h"

/**
 * getcmd - print the prompt and get the user's input
 * @ps: pointer to string
 *
 * Return: 0 on success, -1 if EOF or getline failed to read
 */
int getcmd(char **ps)
{
	ssize_t linelen = 0;
	size_t nbuf = 0;
	char *linebuffer = NULL;

	/* Print the promt */
	write(1, "$ ", 2);

	if (*ps != NULL)
		safe_free(ps);

	linelen = _getline(&linebuffer, &nbuf);
	if (linelen <= 0)
	{
		safe_free(&linebuffer);

		if (linelen == 0)
			printf("\nexit\n");
		else
			perror("Error: ");

		return (-1);
	}
	*ps = linebuffer;
	return (0);
}

/**
 * _getline - reads user's input from standard input and stores
 * the address of the buffer containing the text into *lineptr
 * @lineptr: pointer to string
 * @n: pointer to number of bytes allocated for *lineptr
 *
 * Return: number of characters read. -1 on failure to read a line
 * (including EOF condition).
 */
ssize_t _getline(char **lineptr, size_t *n)
{
	char buffer[BUFSIZE];
	size_t pos = 0;
	ssize_t nread = 0;

	if (*lineptr != NULL)
		safe_free(lineptr);

	*n = BUFSIZE;
	*lineptr = calloc(*n, sizeof(char));
	if (*lineptr == NULL)
		return (-1);

	while ((nread = read(STDIN_FILENO, buffer, BUFSIZE)) > 0)
	{
		pos += nread;
		if (pos == BUFSIZE || pos >= 2 * BUFSIZE)
		{
			if (reallocate_line(lineptr, pos, n))
				return (-1);
		}
		*lineptr = strncat(*lineptr, buffer, nread);
		if (buffer[nread - 1] == '\n')
			break;
	}

	if (nread < 0)
	{
		safe_free(lineptr);
		return (-1);
	}
	(*lineptr)[pos] = '\0';
	return (pos);
}

/**
 * reallocate_line - reallocates memory for storing the line, updating
 * *lineptr and *n as necessary
 * @lineptr: pointer to string
 * @n: pointer to number of bytes allocated for *lineptr
 * @pos: number of characters read so far
 *
 * Return: 0 on success, 1 if realloc fails
 */
int reallocate_line(char **lineptr, size_t pos, size_t *n)
{
	char *newptr = NULL;

	if (pos == BUFSIZE)
		*n *= 2;
	else if (pos == 2 * BUFSIZE)
		*n += 1;
	else if (pos > 2 * BUFSIZE)
		*n += (pos - (2 * BUFSIZE));

	newptr = realloc(*lineptr, *n);
	if (newptr == NULL)
	{
		safe_free(lineptr);
		return (1);
	}

	*lineptr = newptr;

	return (0);
}
