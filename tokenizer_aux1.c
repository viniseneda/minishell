/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_aux1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 13:02:24 by aprotoce          #+#    #+#             */
/*   Updated: 2022/03/01 01:12:22 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_char_in_set(char c, char *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*add_str_to_temp(char *str)
{
	char	*out;

	if (str == NULL || *str == '\0')
		return (temp_str(-2));
	while (*str)
	{
		out = temp_str(*str);
		str++;
	}
	return (out);
}

char	*temp_str(char c)
{
	static char		str[SIZE_OF_TEMP];
	unsigned int	size;

	size = strlen(str);
	if (c == -2)
		return (str);
	if (c == -1)
	{
		*str = '\0';
		return (NULL);
	}
	*(str + size) = c;
	*(str + size + 1) = '\0';
	return (str);
}

char	*temp_str2(char c)
{
	static char		str[SIZE_OF_TEMP];
	unsigned int	size;

	size = strlen(str);
	if (c == -2)
		return (str);
	if (c == -1)
	{
		*str = '\0';
		return (NULL);
	}
	*(str + size) = c;
	*(str + size + 1) = '\0';
	return (str);
}

int	set_errno(int condition, int error)
{
	if (condition)
		errno = error;
	return (condition);
}
