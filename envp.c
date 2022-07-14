/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprotoce <aprotoce@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 15:51:29 by aprotoce          #+#    #+#             */
/*   Updated: 2022/02/26 16:16:54 by aprotoce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_key_value(char *str, char k_or_v)
{
	char	*key;

	temp_str(-1);
	while (*str != '=')
	{
		key = temp_str(*str);
		str++;
	}
	str++;
	if (k_or_v == 'k')
		return (key);
	else
		return (str);
}

char	*join_key_and_value(char *key, char *value)
{
	int		size;
	char	*out;

	size = ft_strlen(key) + ft_strlen(value) + 2;
	out = malloc(size * sizeof(char));
	ft_strlcpy(out, key, ft_strlen(key) + 1);
	ft_strlcat(out, "=", ft_strlen(key) + 2);
	ft_strlcat(out, value, ft_strlen(key) + ft_strlen(value) + 2);
	return (out);
}

int	transfom_tuple_list(t_node *node, char **envp, int i)
{
	while (node != NULL)
	{
		envp[i] = join_key_and_value((char *)node->key, (char *)node->data);
		i--;
		node = node->next;
	}
	return (i);
}

int	transfom_env_list(t_node *node, char **envp, int i)
{
	while (node != NULL)
	{
		if (node->operator)
		{
			envp[i] = join_key_and_value((char *)node->key, (char *)node->data);
			i--;
		}
		node = node->next;
	}
	return (i);
}

char	**make_envp_from_dict(t_node **dict)
{
	char	**envp;
	int		size;
	int		i;

	i = 0;
	size = env_size(dict);
	envp = malloc((size + 1) * sizeof(char *));
	envp[size] = NULL;
	size -= 1;
	while (i < DICT_ARRAY_SIZE)
	{
		size = transfom_env_list(dict[i], envp, size);
		i++;
	}
	return (envp);
}
