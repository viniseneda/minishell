/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 14:23:38 by vvarussa          #+#    #+#             */
/*   Updated: 2022/03/01 01:12:43 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/stat.h>
# include <stdio.h>
# include "libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/types.h>
# include <signal.h>
# include <sys/wait.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>

# define BOLD_H_GREEN	"\e[1;92m"
# define BOLD_H_YELLOW	"\e[1;93m"
# define BOLD_H_BLUE	"\e[1;94m"
# define BOLD_H_MAGENTA	"\e[1;95m"
# define BOLD_H_CYAN		"\e[1;96m"
# define CBW				"\e[1;97m" //color BOLD AND WHITE
# define RESET			"\e[0m"
# define SIZE_OF_TEMP 100
# define DICT_ARRAY_SIZE 50

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

	t_node	*assigment;
	char	**args;
	t_node	**token_list;
	int		last_was_pipe;
}	t_parse_data;

/*minishell*/
//void			sigint_handler(int code);
//void			check_syntax_error(t_node *token_list);
//void			save_envp_to_dict(t_node **dict, char **envp);
//int			interior_loop(char *line, t_node **dict);
//int			main(int argc, char **argv, char **envp);

/*errors*/
int				verify_errno(int error_num, int given, char *error_msg);

/*list*/
void			print_list(t_node *list);
void			print_str_array(char **args, int fd);
int				size_of_list(t_node *list);

/*list free*/
void			free_list(t_node *list);
void			free_str_array(char **args);

/*list nodes*/
t_node			*get_last_node(t_node *list);
t_node			*add_node_to_list(t_node *list, char *data, int is_operator);
void			free_simple_node(t_node *node);
t_node			*remove_node_from_list(t_node *list, t_node *node);

/*dict*/
void			add_dict_value(t_node **dict, char *key,
					char *value, int is_env);
int				env_size(t_node **dict);
t_node			*find_dict_node(t_node **dict, char *key);
char			*find_var(t_node **dict, char *key);
int				change_dict_value(t_node **dict, char *key, char *new_value);
void			change_or_add_value(t_node **dict, char *key, char *value);

/*dict setup*/
unsigned long	get_hash(char *str);
t_node			**create_dict(void);
int				print_dict(t_node **dict);
int				dict_size(t_node **dict);
void			free_dict(t_node **dict);

/*dict_env*/
int				count_env_list(t_node *node);
int				env_size(t_node **dict);
int				print_tuple_list(t_node *node);
int				count_tuple_list(t_node *node);
void			free_tuple_list(t_node *node);

/*envp*/
char			**make_envp_from_dict(t_node **dict);
void			save_envp_to_dict(t_node **dict, char **envp);

/*key and values*/
char			*get_key_value(char *str, char k_or_v);
//char	*join_key_and_value(char *key, char *value)

/*tokenize*/
t_node			*tokenize(char *line);
char			*temp_str(char c);
char			*temp_str2(char c);
char			*add_str_to_temp(char *str);
int				is_char_in_set(char c, char *set);
int				set_errno(int condition, int error);

/*vars*/
char			*replace_vars_in_str(t_node **dict, char *str);
void			replace_vars_in_token_list(t_node **dict, t_node **list_addr);
void			assign_var(t_parse_data data);

/*parser*/
t_parse_data	parse_assigment(t_parse_data data);
void			process_cmd(t_parse_data data);
void			parse(t_node *token_list, t_node **dict);

/*parser aux*/
t_node			*iterate_list(t_node *list, int n);
t_parse_data	parse_cmd_and_args(t_parse_data data);
void			print_parse(t_parse_data data);

/*parser input and output*/
t_parse_data	loop_parse_in(t_parse_data aux, int index);
t_parse_data	parse_in(t_parse_data data);
t_parse_data	loop_parse_out(t_parse_data aux, int index);
t_parse_data	parse_out(t_parse_data data, t_node *other_pipes);

/*nodes*/
t_node			*find_node(t_node *list, char *str);
int				find_node_index(t_node *list, char *str1, char *str2);
void			free_last_node(t_node *list);

/*pipe and heredoc*/
t_node			*split_by_pipe(t_node **list);
int				here_doc(char *delimiter);

/*files*/
int				get_fd_for_file(char *file_name, int overwrite, t_node	**dict);
int				check_error(int i);
void			free_split(char **vector);
int				check_if_directory(char *path);

/*execs*/
char			*check_command_path(t_parse_data data);
//void			check_command_path_part2(t_parse_data data, char pathv);
void			exec_command(t_parse_data data);

/*builtins*/
void			changedir(t_parse_data data);
void			printpwd(t_parse_data data);
void			exit_minishell(t_parse_data data);
int				echo_cmd(t_parse_data data);
int				check_builtin(t_parse_data data);
void			exec_builtin(t_parse_data data);

#endif
