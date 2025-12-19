#ifndef SHELL_H
#define SHELL_H

#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>

typedef struct s_shell
{
	char *line;
	size_t cap;
	int status;
	unsigned long lineno;
	int interactive;
	char *prog; /* argv[0] */
	char **env; /* envp */
} t_shell;

/* Prompt */
void print_prompt(void);

/* Input */
ssize_t read_line(char **line, size_t *cap);
char *get_cmd(char *line);

/* Exec */
int run_cmd(char *cmd, t_shell *sh);

#endif
