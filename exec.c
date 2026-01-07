#include "shell.h"

/**
 * print_not_found - Print command not found error message.
 * @sh: shell state
 * @cmd: command name
 */

static void print_not_found(t_shell *sh, const char *cmd)
{
	fprintf(stderr, "%s: %lu: %s: not found\n",
			sh->prog, sh->lineno, cmd);
}

/**
 * resolve_cmd - Resolve command path, checking for direct
 * path or searching in PATH.
 * @argv: argument array
 * @sh: shell state
 * @cmd_path: output pointer to command path
 * @need_free: output flag indicating if cmd_path needs to be freed
 * Return: 1 if command found, 0 if not found
 */

static int resolve_cmd(char **argv, t_shell *sh,
					   char **cmd_path, int *need_free)
{
	*need_free = 0;

	if (strchr(argv[0], '/'))
	{
		if (access(argv[0], X_OK) != 0)
		{
			print_not_found(sh, argv[0]);
			sh->status = 127;
			return (0);
		}
		*cmd_path = argv[0];
		return (1);
	}

	*cmd_path = find_in_path(argv[0], sh->env);
	if (!*cmd_path)
	{
		print_not_found(sh, argv[0]);
		sh->status = 127;
		return (0);
	}

	*need_free = 1;
	return (1);
}

/**
 * fork_and_exec - Fork and execute the command.
 * @cmd_path: full path to the command
 * @argv: argument array
 * @sh: shell state
 *
 * Return: exit status of the executed command
 */

static int fork_and_exec(char *cmd_path, char **argv, t_shell *sh)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (1);
	}

	if (pid == 0)
	{
		execve(cmd_path, argv, sh->env);
		_exit(127);
	}

	if (waitpid(pid, &status, 0) < 0)
	{
		perror("waitpid");
		return (1);
	}

	if (WIFEXITED(status))
		return (WEXITSTATUS(status));

	return (1);
}

/**
 * run_cmd - Run a command line.
 * @line: command line
 * @sh: shell state
 *
 * Return: exit status of the command
 */

int run_cmd(char *line, t_shell *sh)
{
	char **argv;
	char *cmd_path = NULL;
	int need_free = 0;

	argv = parse_args(line);
	if (!argv || !argv[0])
	{
		free_args(argv);
		return (sh->status);
	}

	if (!resolve_cmd(argv, sh, &cmd_path, &need_free))
	{
		if (need_free)
			free(cmd_path);
		free_args(argv);
		return (sh->status);
	}

	sh->status = fork_and_exec(cmd_path, argv, sh);

	if (need_free)
		free(cmd_path);
	free_args(argv);

	return (sh->status);
}
