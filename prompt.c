#include "shell.h"

/**
 * print_prompt - prints the shell prompt to standard output.
 * Returns: void
 */

void print_prompt(void)
{
	const char *prompt = "#(ಠ_ಠ)$ ";
	write(STDOUT_FILENO, prompt, strlen(prompt));
}
