#include "shell.h"

/**
 * print_prompt - prints the shell prompt to standard output.
 * Returns: void
 */

void print_prompt(void)
{
	write(STDOUT_FILENO, "#cisfun$ ", 9);
}
