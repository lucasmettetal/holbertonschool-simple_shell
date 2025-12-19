#include "shell.h"
/* input.c: functions for reading and parsing input lines
 * from standard input.
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
/* read_line: reads a line from standard input into a dynamically
 * allocated buffer. It removes the trailing newline character.
 * Returns the number of characters read, or -1 on error or EOF.
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
/* get_cmd: extracts the first command from the input line.
 * It skips leading spaces/tabs and cuts the line at the first space/tab.
 * Returns a pointer to the command or NULL if no command is found.
 */
char *get_cmd(char *line)
{
	char *p;

	if (!line)
		return (NULL);

	p = line;

	/* skip leading spaces/tabs */
	while (*p == ' ' || *p == '\t')
		p++;

	if (*p == '\0')
		return (NULL);

	/* cut at first space/tab */
	line = p;
	while (*p && *p != ' ' && *p != '\t')
		p++;

	if (*p)
		*p = '\0';

	return (line);
}
