/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_nodes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprotoce <aprotoce@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 16:34:42 by aprotoce          #+#    #+#             */
/*   Updated: 2022/02/26 16:34:42 by aprotoce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*get_last_node(t_node *list)
{
	while (list->next != NULL)
		list = list->next;
	return (list);
}

void	free_simple_node(t_node *node)
{
	free(node->data);
	free(node);
}

t_node	*add_node_to_list(t_node *list, char *data, int operator)
{
	t_node	*node;

	if (data == NULL)
		return (list);
	node = malloc(sizeof(t_node));
	node->next = NULL;
	node->operator = operator;
	node->data = ft_strdup(data);
	if (list != NULL)
		get_last_node(list)->next = node;
	else
		list = node;
	return (list);
}

t_node	*remove_node_from_list(t_node *list, t_node *node)
{
	t_node	*temp;
	t_node	*first_node;

	first_node = list;
	if (list->next == NULL)
	{
		free(list);
		return (NULL);
	}
	while (list != node && list != NULL)
	{
		temp = list;
		list = list->next;
	}
	if (list != NULL)
	{
		if (first_node == node)
			first_node = list->next;
		else
			temp->next = list->next;
		free(list);
	}
	return (first_node);
}
