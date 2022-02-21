/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvarussa <vvarussa@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 11:37:46 by aprotoce          #+#    #+#             */
/*   Updated: 2022/02/21 11:11:08 by vvarussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int sig)
{
	rl_replace_line("", 1);
	printf("\n["BOLD_H_WHITE"minishell - vvarussa & aprotoce"RESET"]$ ");
}

void	check_syntax_error(t_node *token_list)
{
	t_node *temp;

	temp = token_list;
	if (token_list->operator == 2)
		errno = 506;
	while (token_list != NULL)
	{
		if (token_list->operator == 1)
			if (token_list->next == NULL || token_list->next->operator == 1)
				errno = 505;
		if (token_list->operator == 2)
			if (token_list->next == NULL || token_list->next->operator == 2)
				errno = 506;
		token_list = token_list->next;
	}
	if (errno != 0)
		free_list(temp);
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
			free(line);
			replace_vars_in_token_list(dict, &list);
			check_syntax_error(list);
			if (verify_errno(errno, 501, "Error: no closing quote\n"))
				continue ;
			if (verify_errno(errno, 505, "Sintax error in > or <\n"))
				continue ;
			if (verify_errno(errno, 506, "Syntax error in | \n"))
				continue ;
			parse(list, dict);
		}
	}
	clear_history();
	free_dict(dict);
	printf("\n");
	return (0);
}
