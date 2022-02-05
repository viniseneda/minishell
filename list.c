/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvarussa <vvarussa@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 14:22:37 by vvarussa          #+#    #+#             */
/*   Updated: 2022/01/30 14:27:22 by vvarussa         ###   ########.fr       */
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

int		size_of_list(t_node *list)
{
	int i;

	i = 0;
	while (list != NULL)
	{
		i++;
		list = list->next;
	}
	return(i);
}

t_node	*add_node_to_list(t_node *list, char *data, int operator)
{
	t_node *node;

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

t_node	*add_char_to_list(t_node *list, char *data)
{
	t_node *node;

	if (data == NULL)
		return (list);
	node = malloc(sizeof(t_node));
	node->next = NULL;
	node->data = ft_strdup(data);
	if (list != NULL)
		get_last_node(list)->next = node;
	else
		list = node;
	return (list);
}

void	print_list(t_node *list)
{
	while(list != NULL)
	{
		printf("%s, ", (char *)list->data);
		list = list->next;
	}
	printf("\n");
}

void	print_str_array(char **args)
{
	int i;

	i = 0;
	while(args[i] != NULL)
	{
		printf("%s, ", args[i]);
		i++;
	}
	printf("\n");
}

void	free_str_array(char **args)
{
	int i;

	i = 0;
	while(args[i] != NULL)
	{
		free(args[i]);
		i++;
	}
	free(args);
}


void	free_list(t_node *list)
{
	t_node	*ptr;

	while (list != NULL)
	{
		ptr = list;
		list = list->next;
		free(ptr->data);
		free(ptr);
	}
}
