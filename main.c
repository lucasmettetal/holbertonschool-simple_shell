#include "shell.h"

/**
 * main - Entry point for the simple shell program.
 * @argc: Argument count
 * @argv: Argument vector
 * @envp: Environment variables
 *
 * Return: Exit status of the shell.
 */
int main(int argc, char **argv, char **envp)
{
	t_shell sh;
	ssize_t nread;

	(void)argc;
	sh.line = NULL;
	sh.cap = 0;
	sh.status = 0;
	sh.lineno = 0;
	sh.interactive = isatty(STDIN_FILENO);
	sh.prog = argv[0];
	sh.env = envp;

	while (1)
	{
		if (sh.interactive)
			print_prompt();

		nread = read_line(&sh.line, &sh.cap);
		if (nread == -1)
		{
			if (sh.interactive)
				write(STDOUT_FILENO, "\n", 1);
			break;
		}

		sh.lineno++;

		if (strcmp(sh.line, "exit") == 0 ||
			strcmp(sh.line, "exit ") == 0)
		{
			free(sh.line);
			exit(sh.status);
		}

		run_cmd(sh.line, &sh);
	}

	free(sh.line);
	return (sh.status);
}
