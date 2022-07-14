/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_inout.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprotoce <aprotoce@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 10:52:00 by aprotoce          #+#    #+#             */
/*   Updated: 2022/02/28 22:11:39 by aprotoce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_parse_data	loop_parse_in(t_parse_data aux, int index)
{
	t_node	*temp;

	temp = iterate_list(*aux.token_list, index);
	if (strncmp(temp->data, "<<", 2) == 0)
		aux.fd_in = here_doc(temp->next->data);
	else
		aux.fd_in = get_fd_for_file(temp->next->data, 1, aux.dict);
	*aux.token_list = remove_node_from_list(*aux.token_list, temp->next);
	free(temp->data);
	*aux.token_list = remove_node_from_list(*aux.token_list, temp);
	return (aux);
}

t_parse_data	parse_in(t_parse_data data)
{
	int		index;

	index = find_node_index(*data.token_list, "<", "<<");
	if (index < 0)
	{
		data.fd_in = 0;
		if (data.last_was_pipe)
			data.fd_in = data.pipe2[0];
		return (data);
	}
	while (index >= 0)
	{
		data = loop_parse_in(data, index);
		index = find_node_index(*data.token_list, "<", "<<");
	}
	return (data);
}

t_parse_data	loop_parse_out(t_parse_data aux, int index)
{
	t_node	*temp;

	temp = iterate_list(*aux.token_list, index);
	if (strncmp(temp->data, ">>", 2) == 0)
		aux.fd_out = get_fd_for_file(temp->next->data, 1, aux.dict);
	else
		aux.fd_out = get_fd_for_file(temp->next->data, 0, aux.dict);
	*aux.token_list = remove_node_from_list(*aux.token_list, temp->next);
	free(temp->data);
	*aux.token_list = remove_node_from_list(*aux.token_list, temp);
	return (aux);
}

t_parse_data	parse_out(t_parse_data data, t_node *other_pipes)
{
	int		index;

	index = find_node_index(*data.token_list, ">", ">>");
	if (index < 0)
	{
		if (other_pipes != NULL)
			data.fd_out = data.pipe1[1];
		else
			data.fd_out = 1;
		return (data);
	}
	while (index >= 0)
	{
		data = loop_parse_out(data, index);
		index = find_node_index(*data.token_list, ">", ">>");
	}
	return (data);
}
