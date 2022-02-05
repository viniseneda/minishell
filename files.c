#include "minishell.h"

int	check_error(int i)
{
	if (i < 0)
	{
		perror("error: ");
		exit(errno);
	}
	return (i);
}

void	free_split(char **vector)
{
	int	n;

	n = 0;
	while (vector[n] != NULL)
	{
		free(vector[n]);
		n++;
	}
	free(vector);
}

char	*make_file_path(char *name, char *path)
{
	static	char str[200];

	*str = '\0';
	ft_strlcat(str, path, strlen(path) + 1);
	ft_strlcat(str, "/", strlen(path) + 2);
	ft_strlcat(str, name, strlen(path) + strlen(name) + 2);
	return (str);
}

int	get_fd_for_file(char *file_name, int overwrite, t_node	**dict)
{
	int fd;
	char *path;

	path = find_var(dict, "PWD");
	path = make_file_path(file_name, path);
	if(overwrite)
	{
		fd = open(path, O_RDWR | O_APPEND | O_CREAT, 0666);
	}
	else
	{
		fd = open(path, O_RDWR | O_TRUNC |  O_CREAT, 0666);
	}
	return (fd);
}

char	*check_command_path(t_parse_data data)
{
	char	**pathv;
	char	*program_path;
	char	*temp;
	int		n;

	n = 0;
	pathv = ft_split(find_var(data.dict, "PATH"), ':');
	while (pathv[n] != NULL)
	{
		temp = ft_strjoin(pathv[n], "/");
		program_path = ft_strjoin(temp, data.args[0]);
		free(temp);
		if (!access(program_path, F_OK))
		{
			free_split(pathv);
			return (program_path);
		}
		free(program_path);
		n++;
	}
	free_split(pathv);
	return (NULL);
}

void	exec_command(t_parse_data data)
{
	int	id;

	if (data.bin_path == NULL)
	{
		ft_putstr_fd(data.args[0], 1);
		ft_putstr_fd(" command not found\n", 1);
		check_error(close(data.fd_in));
		check_error(close(data.fd_out));
		return ;
	}
	id = check_error(fork());
	if (id == 0)
	{
		check_error(dup2(data.fd_in, 0));
		check_error(dup2(data.fd_out, 1));
		check_error(execve(data.bin_path, data.args, data.envp));
	}
	if (data.fd_in != 0)
		check_error(close(data.fd_in));
	if (data.fd_out != 1)
		check_error(close(data.fd_out));
	waitpid(id, NULL, WUNTRACED);
}

// int	main(int argc, char **argv, char **envp)
// {
// 	t_node	**dict;
// 	int		fd;

// 	dict = create_dict();
// 	save_envp_to_dict(dict, envp);

// 	fd = get_fd_for_file("blob", 1, dict);
// 	write(fd, "UM TESTE\n", 10);
// 	close(fd);
// }
