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

		/* handle builtin exit */
		if (handle_exit(sh.line, &sh))
			continue;

		/* handle troll art */
		if (handle_troll(sh.line))
			continue;

		/* builtin env */
		if (strcmp(sh.line, "env") == 0)
		{
			int i = 0;

			while (sh.env[i])
			{
				write(STDOUT_FILENO, sh.env[i],
					  strlen(sh.env[i]));
				write(STDOUT_FILENO, "\n", 1);
				i++;
			}
			continue;
		}

		run_cmd(sh.line, &sh);
	}

	free(sh.line);
	return (sh.status);
}
