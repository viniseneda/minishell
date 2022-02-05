/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvarussa <vvarussa@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 11:10:20 by vvarussa          #+#    #+#             */
/*   Updated: 2022/01/30 19:01:35 by vvarussa         ###   ########.fr       */
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

t_node *replace_vars_in_token_list(t_node **dict, t_node *list)
{
	char	*temp;

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
			}
		}
		list = list->next;
	}
}
