/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvarussa <vvarussa@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 11:10:20 by vvarussa          #+#    #+#             */
/*   Updated: 2022/02/06 22:31:03 by vvarussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *replace_vars_in_str(t_node **dict, char *str)
{
	char *key;

	temp_str(-1);
	temp_str2(-1);
	key = NULL;
	if (is_char_in_set('$', str))
	{
		while (*str != '$')
		{
			temp_str(*str);
			str++;
		}
		str++;
		while (*str != '\0' && !is_char_in_set(*str, " 	"))
		{
			key = temp_str2(*str);
			str++;
		}
		if (key == NULL)
			temp_str('$');
		else
			add_str_to_temp(find_var(dict, key));
		while (*str != '\0')
		{
			temp_str(*str);
			str++;
		}
		return (ft_strdup(temp_str(-2)));
	}
	return (NULL);
}

t_node	*remove_node_from_list(t_node *list, t_node *node)
{
	t_node *temp;
	t_node *first_node;

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

void	replace_vars_in_token_list(t_node **dict, t_node **list_addr)
{
	char	*temp;
	t_node	*list;

	list = *list_addr;
	while (list != NULL)
	{
		// printf("%s(%d), ", (char *)list->data, list->operator);
		if (list->operator == 0)
		{
			// printf("%s(%d), ", (char *)list->data, list->operator);
			temp = replace_vars_in_str(dict, list->data);
			if (temp != NULL)
			{
				free(list->data);
				list->data = temp;
				if (ft_strlen(temp) == 0)
				{
					free(list->data);
					*list_addr = remove_node_from_list(*list_addr, list);
					// *list_addr = list->next;
					// print_list(*list_addr);
				}
			}
		}
		list = list->next;
	}
}

void	assign_var(t_parse_data data)
{
	change_or_add_value(data.dict, get_key(data.assigment->data), get_value(data.assigment->data));
}
