/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_colons_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvarussa <vvarussa@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 13:38:37 by vvarussa          #+#    #+#             */
/*   Updated: 2021/11/05 13:41:31 by vvarussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*make_out(char const *s, char const *walker, size_t beg)
{
	char	*out;

	if (*(beg + s) == '\'' || *(beg + s) == '\"')
		out = ft_substr(s, (beg + 1), walker - s - (beg + 1) - 1);
	else
		out = ft_substr(s, beg, walker - s - beg);
	return (out);
}
