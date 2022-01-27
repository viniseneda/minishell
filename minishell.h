/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvarussa <vvarussa@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 14:23:38 by vvarussa          #+#    #+#             */
/*   Updated: 2022/01/27 14:23:43 by vvarussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include <stdlib.h>
#include <errno.h>
#include <readline/readline.h>
#include <readline/history.h>
#define SIZE_OF_TEMP 100
#define DICT_ARRAY_SIZE 50

typedef struct s_node
{
	struct s_node	*next;
	void			*key;
	int				is_operator;
	void			*data;
}	t_node;

typedef struct s_parse_data
{
	char	*in;
	char	*out;
	int		is_here_doc;
	int		is_append;
	t_node	*assigment;
	char	**args;
	t_node	**token_list;
	int		last_was_pipe;
}	t_parse_data;


/*list*/
t_node	*get_last_node(t_node *list);
t_node	*add_node_to_list(t_node *list, char *data, int is_operator);
void	print_list(t_node *list);
void	print_str_array(char **args);
void	free_list(t_node *list);
void	free_str_array(char **args);
void	free_simple_node(t_node *node);
int		size_of_list(t_node *list);

/*dict*/
t_node	**create_dict(void);
int		print_tuple_list(t_node *node);
void	add_dict_value(t_node **dict, char *key, char *value);
int		print_dict(t_node **dict);
void	free_dict(t_node **dict);
t_node	*find_dict_node(t_node **dict, char *key);
int		change_dict_value(t_node **dict, char *key, char *new_value);

/*tokenize*/
t_node	*tokenize(char *line);
int		is_char_in_set(char c, char *set);

/*parser*/
void	parse(t_node *token_list);
