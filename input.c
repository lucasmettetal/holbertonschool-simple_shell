#include "shell.h"

/**
 * strip_newline - removes the trailing newline character from a string.
 * @s: the input string
 * Returns: void
 */

static void strip_newline(char *s)
{
	size_t n;

	if (!s)
		return;
	n = strlen(s);
	if (n > 0 && s[n - 1] == '\n')
		s[n - 1] = '\0';
}

/**
 * read_line - reads a line from standard input into a dynamically
 * allocated buffer.
 * It uses getline to read the line and removes the trailing newline character.
 * @line: pointer to the buffer to store the line
 * @cap: pointer to the size of the buffer
 * Return: number of characters read, or -1 on failure
 */

ssize_t read_line(char **line, size_t *cap)
{
	ssize_t nread;

	nread = getline(line, cap, stdin);
	if (nread == -1)
		return (-1);
	strip_newline(*line);
	return (nread);
}
