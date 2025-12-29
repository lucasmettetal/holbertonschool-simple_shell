#include "shell.h"

/**
 * get_path - return PATH value from env (pointer inside env strings)
 * @env: environment variables
 *
 * Return: pointer to PATH value (after "PATH=") or NULL if not found
 */
char *get_path(char **env)
{
	size_t i = 0;

	if (!env)
		return (NULL);

	while (env[i])
	{
		if (strncmp(env[i], "PATH=", 5) == 0)
			return (env[i] + 5);
		i++;
	}
	return (NULL);
}

/**
 * find_in_path - search cmd in PATH directories
 * @cmd: command name (no '/')
 * @env: environment variables
 *
 * Return: malloc'd full path if found (caller must free), else NULL
 */
char *find_in_path(char *cmd, char **env)
{
	char *path, *copy, *dir, *full;
	size_t len;

	if (!cmd || !*cmd)
		return (NULL);

	path = get_path(env);
	if (!path || !*path)
		return (NULL);

	copy = malloc(strlen(path) + 1);
	if (!copy)
		return (NULL);
	strcpy(copy, path);

	dir = strtok(copy, ":");
	while (dir)
	{
		len = strlen(dir) + 1 + strlen(cmd) + 1;
		full = malloc(len);
		if (!full)
		{
			free(copy);
			return (NULL);
		}

		/* build "dir/cmd" */
		strcpy(full, dir);
		strcat(full, "/");
		strcat(full, cmd);
		if (access(full, X_OK) == 0)
		{
			free(copy);
			return (full);
		}
		free(full);
		dir = strtok(NULL, ":");
	}
	free(copy);
	return (NULL);
}
