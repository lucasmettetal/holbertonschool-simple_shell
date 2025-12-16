#ifndef SHELL_H
#define SHELL_h

#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>

void run_cmd(char *cmd, char *argv0);

#endif
