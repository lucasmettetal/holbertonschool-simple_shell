#include "shell.h"
/* main.c: main function for the simple shell program.
 * It initializes the shell state, reads input lines,
 * extracts commands, and executes them in a loop.
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
