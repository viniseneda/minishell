/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvarussa <vvarussa@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 11:37:46 by aprotoce          #+#    #+#             */
/*   Updated: 2022/01/27 14:25:36 by vvarussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*line;
	int		flagexit;
	int		status;
	t_node	*list;

	flagexit = 1;
	status = 0;
	while (flagexit)
	{
		line = readline("[minishell - vvarussa & aprotoce]$");
		add_history(line);
		if (line == NULL)
			flagexit = 0;
		else if (strcmp(line, "") == 0)
			{
			free(line);
			continue;
			}
		else
		{
			errno = 0;
			list = tokenize(line);
			if (errno == 501)
			{
				free(line);
				printf("no closing quote\n");
				continue;
			}
			parse(list);
		}
		free(line);
	}
	clear_history();
	printf("\n");
	return (0);
}
