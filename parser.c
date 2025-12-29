#include "shell.h"

/**
 * is_sep - Check if a character is a separator (space or tab).
 * @c: The character to check.
 * Return: 1 if separator, 0 otherwise.
 */

static int is_sep(char c)
{
	return (c == ' ' || c == '\t');
}

/**
 * count_words - Count the number of words in a string.
 * @s: The input string.
 * Return: The number of words.
 */

static size_t count_words(char *s)
{
	size_t count = 0;

	while (s && *s)
	{
		while (*s && is_sep(*s))
			s++;
		if (*s)
		{
			count++;
			while (*s && !is_sep(*s))
				s++;
		}
	}
	return (count);
}

/**
 * parse_args - Parse a command line into arguments.
 * @line: The command line string.
 * Return: A NULL-terminated array of argument strings.
 */

char **parse_args(char *line)
{
	char **argv;
	size_t i = 0, words;
	char *p, *start;

	if (!line)
		return (NULL);

	words = count_words(line);
	argv = malloc(sizeof(char *) * (words + 1));
	if (!argv)
		return (NULL);

	p = line;
	while (*p)
	{
		while (*p && is_sep(*p))
			p++;
		if (!*p)
			break;

		start = p;
		while (*p && !is_sep(*p))
			p++;

		if (*p)
			*p++ = '\0';

		argv[i++] = start;
	}
	argv[i] = NULL;
	return (argv);
}

/**
 * free_args - Free the memory allocated for argument array.
 * @args: The argument array to free.
 */

void free_args(char **args)
{
	free(args);
}
