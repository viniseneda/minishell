/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvarussa <vvarussa@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 11:37:46 by aprotoce          #+#    #+#             */
/*   Updated: 2022/02/15 22:48:04 by vvarussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int sig)
{
	rl_replace_line("", 1);
	printf("\n["BOLD_H_WHITE"minishell - vvarussa & aprotoce"RESET"]$ ");
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_node	**dict;
	int		flagexit;
	int		status;
	t_node	*list;

	signal(SIGINT, &sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	flagexit = 1;
	status = 0;
	dict = create_dict();
	save_envp_to_dict(dict, envp);
	while (flagexit)
	{
		line = NULL;
		line = readline("["BOLD_H_WHITE"minishell - vvarussa & aprotoce"RESET"]$ ");
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
			// print_list(list);
			replace_vars_in_token_list(dict, &list);
			// print_list(list);
			if (errno == 501)
			{
				free(line);
				printf("Error: no closing quote\n");
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
