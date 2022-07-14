/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprotoce <aprotoce@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 16:27:30 by aprotoce          #+#    #+#             */
/*   Updated: 2022/02/28 22:12:38 by aprotoce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_command_path_part2(t_parse_data data)
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

char	*check_path_env(t_parse_data data)
{
	int		n;
	char	**pathv;
	char	*temp;
	char	*program_path;

	n = -1;
	pathv = ft_split(find_var(data.dict, "PATH"), ':');
	while (pathv != NULL && pathv[++n] != NULL)
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
	}
	if (pathv != NULL)
		free_split(pathv);
	return (NULL);
}

char	*check_command_path(t_parse_data data)
{
	char	*program_path;

	program_path = check_path_env(data);
	if (program_path)
		return (program_path);
	if (!access(data.args[0], F_OK) && !check_if_directory(data.args[0]))
		return (ft_strdup(data.args[0]));
	else
		check_command_path_part2(data);
	return (NULL);
}

void	exec_command(t_parse_data data)
{
	int		id;
	char	*temp;
	int		wait_id;

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
	free(temp);
}
