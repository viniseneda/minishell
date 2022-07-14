/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprotoce <aprotoce@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 12:06:57 by aprotoce          #+#    #+#             */
/*   Updated: 2022/02/28 22:10:36 by aprotoce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_echo_cmd(t_parse_data data, int i)
{
	while (data.args && data.args[i])
	{
		ft_putstr_fd(data.args[i], data.fd_out);
		i++;
		if (data.args[i] != NULL)
			ft_putchar_fd(' ', data.fd_out);
	}
}

int	echo_cmd(t_parse_data data)
{
	int		flag_n;
	int		i;
	int		ret;

	flag_n = 0;
	i = 1;
	if (data.args[i] != NULL)
	{
		ret = ft_strncmp(data.args[i], "-n", 2);
		while (ret == 0)
		{
			flag_n = 1;
			i++;
			if (data.args[i] == NULL)
				break ;
			ret = ft_strncmp(data.args[i], "-n", 2);
		}
	}
	print_echo_cmd(data, i);
	if (flag_n == 0)
		ft_putchar_fd('\n', data.fd_out);
	change_or_add_value(data.dict, "?", "0");
	return (1);
}
