#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <readline/readline.h>

int	here_doc(char *delimiter)
{
	char	*line;
	int		pipe_fd[2];

	pipe(pipe_fd);
	line = readline("> ");
	while (strcmp(delimiter, line) != 0)
	{
		write(pipe_fd[1], line, strlen(line));
		write(pipe_fd[1], "\n", 1);
		line = readline("> ");
	}
	close(pipe_fd[1]);
	return (pipe_fd[0]);
}

int	main(void)
{
	int fd;
	char c;

	fd = here_doc("aba");
	while(read(fd, &c, 1) != 0)
		write(1, &c, 1);
}
