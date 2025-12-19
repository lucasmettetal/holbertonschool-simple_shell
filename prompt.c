#include "shell.h"

void print_prompt(void)
{
	write(STDOUT_FILENO, "#cisfun$ ", 9);
}
