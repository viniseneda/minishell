/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvarussa <vvarussa@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 11:37:46 by aprotoce          #+#    #+#             */
/*   Updated: 2022/02/28 12:42:51 by vvarussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int code)
{
	(void)code;
	rl_replace_line("", 1);
	printf("\n["CBW"minishell - vvarussa & aprotoce"RESET"]$ ");
}

void	check_syntax_error(t_node *token_list)
{
	t_node	*temp;

	temp = token_list;
	if (token_list != NULL && token_list->operator == 2)
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

void	save_envp_to_dict(t_node **dict, char **envp)
{
	char	*line;

	while (*envp != NULL)
	{
		line = *envp;
		add_dict_value(dict, get_key_value(line, 'k'),
			get_key_value(line, 'v'), 1);
		envp++;
	}
	change_or_add_value(dict, "?", "0");
}

int	interior_loop(char *line, t_node **dict)
{
	t_node	*list;

	if (strcmp(line, "") == 0)
		free(line);
	else
	{
		errno = 0;
		list = tokenize(line);
		free(line);
		replace_vars_in_token_list(dict, &list);
		check_syntax_error(list);
		if (verify_errno(errno, 501, "Error: no closing quote\n"))
			return (1);
		if (verify_errno(errno, 505, "Sintax error in > or <\n"))
			return (1);
		if (verify_errno(errno, 506, "Syntax error in | \n"))
			return (1);
		parse(list, dict);
	}
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_node	**dict;

	if (argc != 1 || ft_strncmp(argv[0], "./minishell", 11))
		exit(1);
	signal(SIGINT, &sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	dict = create_dict();
	save_envp_to_dict(dict, envp);
	while (1)
	{
		line = NULL;
		line = readline("["CBW"minishell - vvarussa & aprotoce"RESET"]$ ");
		add_history(line);
		if (line == NULL)
			break ;
		if (interior_loop(line, dict))
			continue ;
	}
	clear_history();
	free_dict(dict);
	printf("\n");
	return (0);
}
