#include "shell.h"

int run_cmd(char *cmd, t_shell *sh)
{
	pid_t pid;
	int status;
	char *args[2];

	args[0] = cmd;
	args[1] = NULL;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		sh->status = 1;
		return (1);
	}

	if (pid == 0)
	{
		execve(cmd, args, sh->env);

		/* execve failed */
		fprintf(stderr, "%s: %lu: %s: not found\n",
				sh->prog, sh->lineno, cmd);
		_exit(127);
	}

	if (waitpid(pid, &status, 0) < 0)
	{
		perror("waitpid");
		sh->status = 1;
		return (1);
	}

	if (WIFEXITED(status))
		sh->status = WEXITSTATUS(status);

	return (sh->status);
}
