#include "shell.h"
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

void run_cmd(char *cmd, char *argv0)
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
		return;
	}

	if (pid == 0)
	{
		execve(cmd, args, environ);

		/* Si execve échoue : format type /bin/sh */
		fprintf(stderr, "%s: 1: %s: not found\n", argv0, cmd);
		_exit(127);
	}

	if (waitpid(pid, &status, 0) < 0)
		perror("waitpid");
}
