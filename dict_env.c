/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprotoce <aprotoce@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 15:38:07 by aprotoce          #+#    #+#             */
/*   Updated: 2022/02/26 15:38:07 by aprotoce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_env_list(t_node *node)
{
	int	size;

	size = 0;
	while (node != NULL)
	{
		if (node->operator)
			size++;
		node = node->next;
	}
	return (size);
}

int	env_size(t_node **dict)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (i < DICT_ARRAY_SIZE)
	{
		if (*(dict + i) != NULL)
			size += count_env_list(*(dict + i));
		i++;
	}
	return (size);
}

int	print_tuple_list(t_node *node)
{
	int	size;

	size = 0;
	while (node != NULL)
	{
		printf("(%s, %s) ", (char *)node->key, (char *)node->data);
		node = node->next;
		size++;
	}
	return (size);
}

int	count_tuple_list(t_node *node)
{
	int	size;

	size = 0;
	while (node != NULL)
	{
		node = node->next;
		size++;
	}
	return (size);
}

void	free_tuple_list(t_node *node)
{
	t_node	*last;

	while (node != NULL)
	{
		last = node;
		node = node->next;
		free(last->data);
		free(last->key);
		free(last);
	}
}
