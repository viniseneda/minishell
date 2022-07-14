/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprotoce <aprotoce@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 15:32:39 by aprotoce          #+#    #+#             */
/*   Updated: 2022/02/26 15:45:19 by aprotoce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_dict_value(t_node **dict, char *key, char *value, int is_env)
{
	unsigned long	hash;
	t_node			*node;

	if (key == NULL || value == NULL)
		return ;
	node = malloc(sizeof(t_node));
	node->next = NULL;
	node->operator = is_env;
	hash = get_hash(key) % DICT_ARRAY_SIZE;
	if (*(dict + hash) == NULL)
		*(dict + hash) = node;
	else
		get_last_node(*(dict + hash))->next = node;
	node->key = ft_strdup(key);
	node->data = ft_strdup(value);
	node->next = NULL;
}

t_node	*find_dict_node(t_node **dict, char *key)
{
	int		hash;
	t_node	*node;

	hash = get_hash(key) % DICT_ARRAY_SIZE;
	if (dict[hash] != NULL)
	{
		node = dict[hash];
		while (node != NULL)
		{
			if (ft_strncmp(node->key, key, ft_strlen(key)) == 0)
				return (node);
			node = node->next;
		}
	}
	return (NULL);
}

int	change_dict_value(t_node **dict, char *key, char *new_value)
{
	t_node	*node;

	node = find_dict_node(dict, key);
	if (node == NULL)
		return (0);
	free(node->data);
	node->data = ft_strdup(new_value);
	return (1);
}

char	*find_var(t_node **dict, char *key)
{
	t_node	*node;

	node = find_dict_node(dict, key);
	if (node == NULL)
		return (NULL);
	return (node->data);
}

void	change_or_add_value(t_node **dict, char *key, char *value)
{
	if (!change_dict_value(dict, key, value))
		add_dict_value(dict, key, value, 0);
}
