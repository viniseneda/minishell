#include "minishell.h"

int check_error(int i)
{
	if (i < 0)
	{
		perror("error: ");
		exit(errno);
	}
	return (i);
}

void free_split(char **vector)
{
	int n;

	n = 0;
	while (vector[n] != NULL)
	{
		free(vector[n]);
		n++;
	}
	free(vector);
}

char *make_file_path(char *name, char *path)
{
	static char str[200];

	*str = '\0';
	ft_strlcat(str, path, strlen(path) + 1);
	ft_strlcat(str, "/", strlen(path) + 2);
	ft_strlcat(str, name, strlen(path) + strlen(name) + 2);
	return (str);
}

int get_fd_for_file(char *file_name, int overwrite, t_node **dict)
{
	int fd;
	char *path;

	path = find_var(dict, "PWD");
	path = make_file_path(file_name, path);
	if (overwrite)
	{
		fd = open(path, O_RDWR | O_APPEND | O_CREAT, 0666);
	}
	else
	{
		fd = open(path, O_RDWR | O_TRUNC | O_CREAT, 0666);
	}
	free(file_name);
	return (fd);
}

int	check_if_directory(char *path)
{
	struct stat sb;

	if(stat(path, &sb) == -1)
		return (0);
	if(S_ISDIR(sb.st_mode & __S_IFMT))
	{
		return(1);
	}
	return(0);
}

char *check_command_path(t_parse_data data)
{
	char **pathv;
	char *program_path;
	char *temp;
	int n;

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
	// printf("args[0]: %s\n", data.args[0]);
	if (!access(data.args[0], F_OK) && !check_if_directory(data.args[0]))
		return(data.args[0]);
	else
	{
		if (check_if_directory(data.args[0]))
		{
			change_or_add_value(data.dict, "?", "126");
			printf("bash: %s: Is a directory\n", data.args[0]);
		}
		else
		{
			change_or_add_value(data.dict, "?", "127");
			printf("%s command not found\n", data.args[0]);
		}
	}
	return (NULL);
}

void exec_command(t_parse_data data)
{
	int id;
	char *temp;
	int wait_id;

	// if (data.bin_path == NULL)
	// {
	// 	ft_putstr_fd(data.args[0], 1);
	// 	ft_putstr_fd(" command not found\n", 1);
	// 	// check_error(close(data.fd_in));
	// 	// check_error(close(data.fd_out));
	// 	return;
	// }
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
	waitpid(id, &wait_id, WUNTRACED);
	temp = ft_itoa(WEXITSTATUS(wait_id));
	change_or_add_value(data.dict, "?", temp);
	// printf("ARGS: ");
	// print_str_array(data.args);
	// free_str_array(data.args);
	free(temp);
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
