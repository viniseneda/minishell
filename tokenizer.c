/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 14:24:42 by vvarussa          #+#    #+#             */
/*   Updated: 2022/03/01 01:12:20 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//#define sintax " 	'\"|<>"

void	add_token_to_list(t_node **list, char *token, int operator)
{
	*list = add_node_to_list(*list, token, operator);
	temp_str(-1);
}

void	token_quote(t_node **list, char **line, char q)
{
	char	*token;

	if (**line == q)
	{
		*line = *line + 1;
		if (**line == q)
		{
			*line = *line + 1;
			return ;
		}
		while (**line != q && **line)
		{
			token = temp_str(**line);
			*line = *line + 1;
		}
		if (set_errno(**line != q, 501))
			return ;
		if (q == '\"')
			add_token_to_list(list, token, 0);
		else
			add_token_to_list(list, token, -1);
		*line = *line + 1;
	}
}

int	check_for_quote(t_node **list, char **line)
{
	if (is_char_in_set(**line, "'\""))
	{
		token_quote(list, line, '\"');
		token_quote(list, line, '\'');
		return (1);
	}
	return (0);
}

void	add_operand_to_list(t_node **list, char **line)
{
	if (is_char_in_set(**line, "<>") && **line == *(*line + 1))
	{
		temp_str(**line);
		add_token_to_list(list, temp_str(**line), 1);
		*line = *line + 1;
	}
	else if (is_char_in_set(**line, "<>"))
		add_token_to_list(list, temp_str(**line), 1);
	else if (is_char_in_set(**line, "|"))
		add_token_to_list(list, temp_str(**line), 2);
}

t_node	*tokenize(char *line)
{
	char	*token;
	t_node	*list;

	list = NULL;
	temp_str(-1);
	while (*line)
	{
		token = NULL;
		while (!is_char_in_set(*line, " 	'\"|<>") && *line)
		{
			token = temp_str(*line);
			line++;
		}
		add_token_to_list(&list, token, 0);
		if (!check_for_quote(&list, &line) && *line)
		{
			add_operand_to_list(&list, &line);
			line++;
		}
	}
	return (list);
}
