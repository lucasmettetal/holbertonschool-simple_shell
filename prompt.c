#include "shell.h"

/**
 * print_prompt - displays the shell prompt if input is from a terminal
 * Return: void
 */

void print_prompt(void)
{
	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "#cisfun$ ", 9);
}
