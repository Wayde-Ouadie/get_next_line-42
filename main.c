#include "get_next_line.h"
int main()
{
	char *line;
	int fd;
	int i;

	i = 0;
	fd = open("test.txt", O_RDONLY);
	while (i < 5)
	{
		line = get_next_line(fd);
		printf("%s\n", line);
		free(line);
		i++;
	}
	close(fd);
	return (0);
}