#include "shell.h"
#include <fcntl.h>

int handle_troll(char *line)
{
	int fd;
	char buf[1024];
	ssize_t n;

	if (!line)
		return (0);

	if (strcmp(line, "lucas") != 0)
		return (0);

	fd = open("Asset/lucas.ascii", O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		return (1);
	}

	while ((n = read(fd, buf, sizeof(buf))) > 0)
		write(STDOUT_FILENO, buf, n);

	close(fd);
	return (1);
}
