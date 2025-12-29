#include "shell.h"

/**
 * split_line - Split a command line into arguments using strtok.
 * @line: The command line string. Modified in place.
 * Return: A NULL-terminated array of argument strings.
 */

static char **split_line(char *line)
{
	char **argv;
	size_t i = 0;
	char *tok;

	if (!line)
		return (NULL);

	/* max 64 args for 0.1+ (no realloc) */
	argv = malloc(sizeof(char *) * 65);
	if (!argv)
		return (NULL);

	tok = strtok(line, " \t");
	while (tok && i < 64)
	{
		argv[i++] = tok;
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

		/* execve failed */
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
