/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprotoce <aprotoce@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 16:19:33 by aprotoce          #+#    #+#             */
/*   Updated: 2022/02/26 17:10:53 by aprotoce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	static char	str[200];

	*str = '\0';
	ft_strlcat(str, path, strlen(path) + 1);
	ft_strlcat(str, "/", strlen(path) + 2);
	ft_strlcat(str, name, strlen(path) + strlen(name) + 2);
	return (str);
}

int	get_fd_for_file(char *file_name, int overwrite, t_node **dict)
{
	int		fd;
	char	*path;

	path = find_var(dict, "PWD");
	path = make_file_path(file_name, path);
	if (overwrite)
		fd = open(path, O_RDWR | O_APPEND | O_CREAT, 0666);
	else
		fd = open(path, O_RDWR | O_TRUNC | O_CREAT, 0666);
	free(file_name);
	return (fd);
}

int	check_if_directory(char *path)
{
	struct stat	sb;

	if (stat(path, &sb) == -1)
		return (0);
	if (S_ISDIR(sb.st_mode & __S_IFMT))
		return (1);
	return (0);
}
