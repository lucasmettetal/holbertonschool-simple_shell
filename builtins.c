#include "shell.h"

/**
 * handle_exit - handle the exit builtin
 * @line: input line
 * @sh: shell state
 *
 * Return: 1 if exit was handled, 0 otherwise
 */
int handle_exit(char *line, t_shell *sh)
{
	if (!line)
		return (0);

	if (strcmp(line, "exit") == 0)
	{
		free(sh->line);
		exit(sh->status);
	}
	return (0);
}
