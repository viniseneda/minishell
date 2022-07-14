/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_nodes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprotoce <aprotoce@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 15:05:33 by aprotoce          #+#    #+#             */
/*   Updated: 2022/02/26 15:05:33 by aprotoce         ###   ########.fr       */
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

int	find_node_index(t_node *list, char *str1, char *str2)
{
	int	n;

	n = 0;
	while (list != NULL)
	{
		if (ft_strncmp(list->data, str1, strlen(list->data)) == 0
			|| ft_strncmp(list->data, str2, strlen(list->data)) == 0)
			return (n);
		n++;
		list = list->next;
	}
	return (-1);
}

t_node	*get_before_last_node(t_node *list)
{
	t_node	*temp;

	if (list == NULL || list->next == NULL)
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
	t_node	*temp;

	temp = get_before_last_node(list);
	free(temp->next->data);
	free(temp->next);
	temp->next = NULL;
}
