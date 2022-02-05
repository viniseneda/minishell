/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvarussa <vvarussa@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 14:23:38 by vvarussa          #+#    #+#             */
/*   Updated: 2022/02/05 17:53:50 by vvarussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <errno.h>
#include <readline/readline.h>
#include <readline/history.h>
#define SIZE_OF_TEMP 100
#define DICT_ARRAY_SIZE 50

typedef struct s_node
{
	struct s_node	*next;
	void			*key;
	int				operator;
	void			*data;
}	t_node;

typedef struct s_parse_data
{
	int		fd_in;
	int		fd_out;
	int		pipe1[2];
	int		pipe2[2];
	char	**envp;
	char	*bin_path;
	t_node	**dict;
	int		is_here_doc;
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
int		dict_size(t_node **dict);
void	free_dict(t_node **dict);
t_node	*find_dict_node(t_node **dict, char *key);
char	*find_var(t_node **dict, char *key);
int		change_dict_value(t_node **dict, char *key, char *new_value);
void	change_or_add_value(t_node **dict, char *key, char *value);

/*envp*/
char	**make_envp_from_dict(t_node **dict);
void	save_envp_to_dict(t_node **dict, char **envp);

/*tokenize*/
t_node	*tokenize(char *line);
char	*temp_str(char c);
char	*temp_str2(char c);
char	*add_str_to_temp(char *str);
int		is_char_in_set(char c, char *set);

/*vars*/
char	*replace_vars_in_str(t_node **dict, char *str);
t_node	*replace_vars_in_token_list(t_node **dict, t_node *list);

/*parser*/
void	parse(t_node *token_list, t_node **dict);

/*files*/
int		get_fd_for_file(char *file_name, int overwrite, t_node	**dict);
char	*check_command_path(t_parse_data data);
int		check_error(int i);
void	exec_command(t_parse_data data);
