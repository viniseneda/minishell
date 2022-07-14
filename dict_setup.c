/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict_setup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvarussa <vvarussa@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 15:41:48 by aprotoce          #+#    #+#             */
/*   Updated: 2022/02/28 12:42:45 by vvarussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned long	get_hash(char *str)
{
	unsigned long	hash;
	int				c;

	hash = 5381;
	while (*str)
	{
		c = *str;
		str++;
		hash = ((hash << 5) + hash) + c;
	}
	return (hash);
}

t_node	**create_dict(void)
{
	t_node	**dict;
	int		i;

	i = 0;
	dict = malloc(sizeof(t_node *) * DICT_ARRAY_SIZE);
	if (dict == NULL)
		exit (100);
	while (i < DICT_ARRAY_SIZE)
	{
		dict[i] = NULL;
		i++;
	}
	return (dict);
}

int	print_dict(t_node **dict)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (i < DICT_ARRAY_SIZE)
	{
		if (*(dict + i) != NULL)
		{
			size += print_tuple_list(*(dict + i));
		}
		i++;
	}
	printf("\n");
	return (size);
}

int	dict_size(t_node **dict)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (i < DICT_ARRAY_SIZE)
	{
		if (*(dict + i) != NULL)
		{
			size += count_tuple_list(*(dict + i));
		}
		i++;
	}
	return (size);
}

void	free_dict(t_node **dict)
{
	int	i;

	i = 0;
	while (i < DICT_ARRAY_SIZE)
	{
		if (dict[i] != NULL)
			free_tuple_list(dict[i]);
		i++;
	}
	free(dict);
}
