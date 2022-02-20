/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprotoce <aprotoce@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 13:47:28 by aprotoce          #+#    #+#             */
/*   Updated: 2022/02/08 13:47:28 by aprotoce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_minishell(t_parse_data data)
{
	int numeroerro;

	numeroerro = 0;
	if (!data.last_was_pipe)
	{
		if (data.args[1])
		numeroerro = ft_atoi(data.args[1]);
		//printf("%i\n", numeroerro);
		//dar free em tudo soh fiz num argumento
		//print_str_array(data.args);
		free_str_array(data.args);
		free_dict(data.dict);
		free_str_array(data.envp);
		// rl_clear_history();
		exit(numeroerro);
	}

}
