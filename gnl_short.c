#include <stdlib.h> // malloc
#include <stdio.h> // printf
#include <unistd.h> // read
#include <fcntl.h> // open


int	gnl(char **line)
{
	int	i = 0;
	int bwr;
	char ch;
	char *buffer = malloc(100000);

	*line = buffer;
	while((bwr = read(0, &ch, 1)) > 0 && ch != '\n')
		buffer[i++] = ch;
	buffer[i] = '\0';
	return (bwr);
}

int main(void)
{
	int fd = open("/home/bnidia/gnl/test1.txt", O_RDONLY);

	printf("%s", gnl(fd));
	return (0);
}