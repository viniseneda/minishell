/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe_hd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 15:13:37 by aprotoce          #+#    #+#             */
/*   Updated: 2022/03/01 01:46:06 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*split_by_pipe(t_node **list)
{
	t_node	*command;
	t_node	*temp;

	command = *list;
	temp = find_node(*list, "|");
	if (temp == NULL)
	{
		command = *list;
		*list = NULL;
		return (command);
	}
	if (temp != NULL && temp->next->operator == 2)
	{
		errno = 502;
		free_list(*list);
		return (NULL);
	}
	*list = temp->next;
	temp->next = NULL;
	free_last_node(command);
	return (command);
}

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
		free(line);
		line = readline("> ");
	}
	free(delimiter);
	free(line);
	close(pipe_fd[1]);
	return (pipe_fd[0]);
}
