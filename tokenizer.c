/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvarussa <vvarussa@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 14:24:42 by vvarussa          #+#    #+#             */
/*   Updated: 2022/01/30 14:46:42 by vvarussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define sintax " 	'\"|<>"
int numero;

int		is_char_in_set(char c, char *set)
{
	while(*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return 0;
}

void reset_temp_str(char *str)
{
	*str = '\0';
}

char *temp_str(char c)
{
	static char str[SIZE_OF_TEMP];
	unsigned int size;

	size = strlen(str);
	if (c == -2)
		return (str);
	if (c == -1)
	{
		reset_temp_str(str);
		return (NULL);
	}
	*(str + size) = c;
	*(str + size + 1) = '\0';
	return (str);
}

char *temp_str2(char c)
{
	static char str[SIZE_OF_TEMP];
	unsigned int size;

	size = strlen(str);
	if (c == -2)
		return (str);
	if (c == -1)
	{
		reset_temp_str(str);
		return (NULL);
	}
	*(str + size) = c;
	*(str + size + 1) = '\0';
	return (str);
}

char *add_str_to_temp(char *str)
{
	char *out;

	if (str == NULL || *str == '\0')
		return (temp_str(-2));
	while(*str)
	{
		out = temp_str(*str);
		str++;
	}
	return (out);
}

void	add_token_to_list(t_node **list, char *token, int operator)
{
	*list = add_node_to_list(*list, token, operator);
	temp_str(-1);
}



void	token_quote(t_node **list, char **line, char q)
{
	char *token;

	if (**line == q)
	{
		// add_token_to_list(list, temp_str(**line), 1); // are the quotes thenselves operators?
		*line = *line + 1;
		while(**line != q && **line)
		{
			token = temp_str(**line);
			*line = *line + 1;
		}
		if (**line != q)  //exit if quote not complete
		{
			errno = 501;
			return;
		}
		if (q == '\"')
			add_token_to_list(list, token, 0);
		else
			add_token_to_list(list, token, -1);
		// add_token_to_list(list, temp_str(**line), 1);
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
	if(is_char_in_set(**line, "|<>") && **line == *(*line + 1) )
	{
		temp_str(**line);
		add_token_to_list(list, temp_str(**line), 1);
		*line = *line + 1;
	}
	else if (is_char_in_set(**line, "|<>"))
		add_token_to_list(list, temp_str(**line), 1);
}

t_node *tokenize(char *line)
{
	char	*token;
	t_node	*list;

	list = NULL;
	temp_str(-1);
	while(*line)
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

// int	main(void)
// {
// 	char *line;
// 	t_node *list;

// 	line = readline(">> ");
// 	list = tokenize(line);
// 	free(line);
// 	print_list(list);
// 	free_list(list);
// 	// printf("%s\n", line);
// }
