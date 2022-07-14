/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprotoce <aprotoce@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 21:49:35 by aprotoce          #+#    #+#             */
/*   Updated: 2022/02/26 21:49:35 by aprotoce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	verify_errno(int error_num, int given, char *error_msg)
{
	if (error_num == given)
	{
		printf("%s", error_msg);
		return (1);
	}
	return (0);
}
