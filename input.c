#include "shell.h"

static void strip_newline(char *s)
{
    size_t n;

    if (!s)
        return;
    n = strlen(s);
    if (n > 0 && s[n - 1] == '\n')
        s[n - 1] = '\0';
}

ssize_t read_line(char **line, size_t *cap)
{
    ssize_t nread;

    nread = getline(line, cap, stdin);
    if (nread == -1)
        return (-1);
    strip_newline(*line);
    return (nread);
}

char *get_cmd(char *line)
{
    char *p;

    if (!line)
        return (NULL);

    p = line;

    /* skip leading spaces/tabs */
    while (*p == ' ' || *p == '\t')
        p++;

    if (*p == '\0')
        return (NULL);

    /* cut at first space/tab */
    line = p;
    while (*p && *p != ' ' && *p != '\t')
        p++;

    if (*p)
        *p = '\0';

    return (line);
}