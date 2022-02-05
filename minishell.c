/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvarussa <vvarussa@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 11:37:46 by aprotoce          #+#    #+#             */
/*   Updated: 2022/02/05 17:54:12 by vvarussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_node	**dict;
	int		flagexit;
	int		status;
	t_node	*list;

	flagexit = 1;
	status = 0;
	dict = create_dict();
	save_envp_to_dict(dict, envp);
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
			replace_vars_in_token_list(dict, list);
			// print_list(list);
			if (errno == 501)
			{
				free(line);
				printf("no closing quote\n");
				continue;
			}
			parse(list, dict);
		}
		free(line);
	}
	clear_history();
	printf("\n");
	return (0);
}
