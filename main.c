#include "shell.h"

/**
 * main - entry point for the simple shell program.
 * It initializes the shell state, enters a loop to read and execute commands,
 * and handles interactive prompts.
 * @argc: argument count
 * @argv: argument vector
 * @envp: environment variables
 * Return: exit status of the shell
 */

int main(int argc, char **argv, char **envp)
{
	t_shell sh;
	ssize_t nread;
	char *cmd;

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

		cmd = get_cmd(sh.line);
		if (!cmd)
			continue;

		run_cmd(cmd, &sh);
	}

	free(sh.line);
	return (sh.status);
}
