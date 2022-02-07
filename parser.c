/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvarussa <vvarussa@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 14:23:55 by vvarussa          #+#    #+#             */
/*   Updated: 2022/02/06 20:14:46 by vvarussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*find_node(t_node *list, char *str)
{
	while (list != NULL)
	{
		if (ft_strncmp(list->data, str, strlen(str)) == 0)
			return (list);
		list = list->next;
	}
	return (NULL);
}

t_node	*iterate_list(t_node *list, int n)
{
	int i;

	i = 0;
	while (i < n)
	{
		list = list->next;
		i++;
	}
	return (list);
}

int	find_node_index(t_node *list, char *str1, char *str2)
{
	int	n;

	n = 0;
	while (list != NULL)
	{
		if (ft_strncmp(list->data, str1, strlen(list->data)) == 0 || ft_strncmp(list->data, str2, strlen(list->data)) == 0)
			return (n);
		n++;
		list = list->next;
	}
	return (-1);
}

t_node	*get_before_last_node(t_node *list)
{
	t_node	*temp;

	if(list == NULL || list->next == NULL)
		return (NULL);
	while (list->next != NULL)
	{
		temp = list;
		list = list->next;
	}
	return (temp);
}

void	free_last_node(t_node *list)
{
	t_node *temp;

	temp = get_before_last_node(list);
	free(temp->next->data);
	free(temp->next);
	temp->next = NULL;
}

t_node	*split_by_pipe(t_node **list)
{
	t_node *command;
	t_node *temp;

	command = *list;
	temp = find_node(*list, "|");
	if (temp == NULL)
	{
		command = *list;
		*list = NULL;
		return (command);
	}
	*list = temp->next;
	temp->next = NULL;
	free_last_node(command);
	return (command);
}

t_parse_data	parse_in(t_parse_data data)
{
	int	index;
	t_node *temp;

	index = find_node_index(*data.token_list, "<", "<<");
	if (index < 0)
	{
		if (data.last_was_pipe)
			data.fd_in = data.pipe2[0];
		else
			data.fd_in = 0;
		return (data);
	}
	//fazer condição de  erro de quando nao tem nada depois do >
	while (index > 0)
	{
		temp = iterate_list(*data.token_list, index);
		if (strncmp(temp->data, "<<", 2) == 0)
			data.is_here_doc = 1;
		if (temp->next == NULL || temp->next->operator > 0)
		{
			errno = 502; // sintax error
			return (data);
		}
		data.fd_in = get_fd_for_file(temp->next->data, 0, data.dict);
		iterate_list(*data.token_list, index - 1)->next = temp->next->next;
		free(temp->next);
		free_simple_node(temp);
		index = find_node_index(*data.token_list, "<", "<<"); // make a way to check for here dock
	}
	return (data);
}

t_parse_data	parse_out(t_parse_data data, t_node *other_pipes)
{
	int	index;
	t_node *temp;

	index = find_node_index(*data.token_list, ">", ">>");
	if (index < 0)
	{
		if (other_pipes != NULL)
			data.fd_out = data.pipe1[1];
		else
			data.fd_out = 1;
		return (data);
	}
	//fazer condição de  erro de quando nao tem nada depois do >
	while (index > 0)
	{
		temp = iterate_list(*data.token_list, index);
		if (temp->next == NULL || temp->next->operator > 0)
		{
			errno = 502; // sintax error
			return (data);
		}
		if (strncmp(temp->data, ">>", 2) == 0)
			data.fd_out = get_fd_for_file(temp->next->data, 1, data.dict);
		else
			data.fd_out = get_fd_for_file(temp->next->data, 0, data.dict);
		iterate_list(*data.token_list, index - 1)->next = temp->next->next;
		free(temp->next);
		free_simple_node(temp);
		index = find_node_index(*data.token_list, ">", ">>");
	}
	// printf("(%d)", data.is_append);
	return (data);
}


t_parse_data	parse_assigment(t_parse_data data)
{
	t_node	*node;

	node = *data.token_list;
	if (is_char_in_set('=', node->data))
	{
		if (data.assigment != NULL)
		{
			free(data.assigment->data);
			free(data.assigment);
		}
		data.assigment = node;
		*data.token_list = node->next;
	}
	return(data);
}

t_parse_data	parse_cmd_and_args(t_parse_data data)
{
	t_node	*token_list;
	t_node	*temp;
	int i;

	i = 0;
	token_list = *data.token_list;
	// printf("size of list: %d\n", size_of_list(token_list));
	data.args = malloc(sizeof(char *) * (size_of_list(token_list) + 1));
	while (token_list != NULL)
	{
		temp = token_list;
		data.args[i] = token_list->data;
		// printf("%s\n", data.args[i]);
		token_list = token_list->next;
		i++;
		free(temp);
	}
	data.args[i] = NULL;
	return (data);

}

void	print_parse(t_parse_data data)
{
	t_node *as;

	as = data.assigment;
	printf("in: %d\n", data.fd_in);
	printf("out: %d\n", data.fd_out);
	printf("is here doc: %d\n", data.is_here_doc);
	if (as != NULL)
		printf("assigment: %s\n", (char *)as->data);
	printf("arguments: ");
	print_str_array(data.args);
	printf("\n");
}

void	free_parse_data(t_parse_data data)
{
	free_str_array(data.args);
}

void	parse(t_node *token_list, t_node **dict)
{
	t_node			*sub_token_list;
	t_parse_data	data;

	data.last_was_pipe = 0;
	data.assigment = NULL;
	data.dict = dict;
	while(token_list != NULL)
	{
		data.pipe2[0] = data.pipe1[0];
		data.pipe2[1] = data.pipe1[1];
		pipe(data.pipe1);
		data.is_here_doc = 0;
		sub_token_list  = split_by_pipe(&token_list);
		data.token_list = &sub_token_list;


		data = parse_in(data);
		data = parse_out(data, token_list);

		if (errno == 502)
		{
			printf("Sintax error\n");
			return ;
		}

		data = parse_assigment(data);
		data = parse_cmd_and_args(data);
		// free_list(sub_token_list);
		// print_parse(data);
		if (token_list == NULL && data.assigment != NULL && !data.last_was_pipe)
			assign_var(data);
		else if (*data.args != NULL)
		{
			data.envp = make_envp_from_dict(data.dict);
			data.bin_path = check_command_path(data);
			exec_command(data);
			free_str_array(data.envp);
		}
		free_parse_data(data);
		data.last_was_pipe = 1;
	}
}