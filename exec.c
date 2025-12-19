#include "shell.h"

/**
 * split_line - Split a line into tokens (argv style).
 * @line: Input line (modified in place).
 *
 * Return: NULL-terminated array of tokens, or NULL on failure.
 */
char **split_line(char *line)
{
	size_t cap = 8, i = 0;
	char **argv, **tmp;
	char *tok;

	if (!line)
		return (NULL);

	argv = malloc(sizeof(char *) * cap);
	if (!argv)
		return (NULL);

	tok = strtok(line, " \t");
	while (tok)
	{
		argv[i++] = tok;

		if (i + 1 >= cap)
		{
			cap *= 2;
			tmp = realloc(argv, sizeof(char *) * cap);
			if (!tmp)
			{
				free(argv);
				return (NULL);
			}
			argv = tmp;
		}

		tok = strtok(NULL, " \t");
	}
	argv[i] = NULL;

	return (argv);
}

/**
 * run_cmd - Execute a command line using fork and execve.
 * @line: Full input line (command + arguments). Modified in place.
 * @sh: Shell state.
 *
 * Return: Exit status of the command.
 */
int run_cmd(char *line, t_shell *sh)
{
	pid_t pid;
	int status;
	char **argv;

	argv = split_line(line);
	if (!argv || !argv[0])
	{
		free(argv);
		return (sh->status);
	}

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		free(argv);
		sh->status = 1;
		return (1);
	}

	if (pid == 0)
	{
		execve(argv[0], argv, sh->env);

		fprintf(stderr, "%s: %lu: %s: not found\n",
				sh->prog, sh->lineno, argv[0]);
		_exit(127);
	}

	if (waitpid(pid, &status, 0) < 0)
	{
		perror("waitpid");
		free(argv);
		sh->status = 1;
		return (1);
	}

	free(argv);

	if (WIFEXITED(status))
		sh->status = WEXITSTATUS(status);

	return (sh->status);
}
