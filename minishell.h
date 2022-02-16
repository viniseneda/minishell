/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvarussa <vvarussa@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 14:23:38 by vvarussa          #+#    #+#             */
/*   Updated: 2022/02/16 09:10:08 by vvarussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <stdio.h>
#include "libft.h"
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>
#include <errno.h>
#include <readline/readline.h>
#include <readline/history.h>
# define BOLD_H_GREEN	"\e[1;92m"
# define BOLD_H_YELLOW	"\e[1;93m"
# define BOLD_H_BLUE	"\e[1;94m"
# define BOLD_H_MAGENTA	"\e[1;95m"
# define BOLD_H_CYAN	"\e[1;96m"
# define BOLD_H_WHITE	"\e[1;97m"
# define RESET			"\e[0m"
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
	int		is_here_doc;
	char	**envp;
	char	*bin_path;
	t_node	**dict;

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
t_node	*remove_node_from_list(t_node *list, t_node *node);

/*dict*/
int		print_tuple_list(t_node *node);

unsigned long	get_hash(char *str);
t_node	**create_dict(void);
int		print_tuple_list(t_node *node);
void	add_dict_value(t_node **dict, char *key, char *value, int is_env);
int		print_dict(t_node **dict);
int		env_size(t_node **dict);
int		dict_size(t_node **dict);
void	free_dict(t_node **dict);
t_node	*find_dict_node(t_node **dict, char *key);
char	*find_var(t_node **dict, char *key);
int		change_dict_value(t_node **dict, char *key, char *new_value);
void	change_or_add_value(t_node **dict, char *key, char *value);

/*envp*/
char	**make_envp_from_dict(t_node **dict);
char	*get_key(char *str);
char	*get_value(char *str);
void	save_envp_to_dict(t_node **dict, char **envp);

/*tokenize*/
t_node	*tokenize(char *line);
char	*temp_str(char c);
char	*temp_str2(char c);
char	*add_str_to_temp(char *str);
int		is_char_in_set(char c, char *set);

/*vars*/
char	*replace_vars_in_str(t_node **dict, char *str);
void	replace_vars_in_token_list(t_node **dict, t_node **list_addr);
void	assign_var(t_parse_data data);

/*parser*/
void	parse(t_node *token_list, t_node **dict);

/*files*/
int		get_fd_for_file(char *file_name, int overwrite, t_node	**dict);
char	*check_command_path(t_parse_data data);
int		check_error(int i);
void	exec_command(t_parse_data data);

/*builtins*/
void	changeDir(t_parse_data data);
void	printpwd(t_parse_data data);
void	exit_minishell(t_parse_data data);
int		echo_cmd(t_parse_data data);
int		check_builtin(t_parse_data data);
void	exec_builtin(t_parse_data data);

