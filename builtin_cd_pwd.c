/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_pwd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprotoce <aprotoce@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 12:50:48 by aprotoce          #+#    #+#             */
/*   Updated: 2022/02/09 12:50:48 by aprotoce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void printpwd(t_parse_data data)
{
	char cwd[4096];
	
	printf("%s\n", getcwd(cwd, sizeof(cwd)));
}


static int	cd_args(char **cmd, int i)
{
	int numeroerro;

	while (cmd[i])
		i++;
	if (i > 2)
	{
		ft_putstr_fd("Minishell: cd: too many arguments\n", STDERR_FILENO);
		numeroerro = 1;
	}
	return (i);
}


void changeDir(t_parse_data data)
{
	char cwd[4096];
    int status = chdir(data.args[1]);
    
	if (data.args[1] == " " || data.args[1] == "") //se nao houver parametro, se nao quisermos, deixar com status != 0
	{
		getcwd(cwd, 4096);
		//printf("%s%s%i%s\n", cwd, " - #chdir:", status, ")"); /*para ver se esta certo*/
		return;
	}	
	if (status == 0)
	{
		getcwd(cwd, 4096);
		chdir(cwd);
		//printf("%s%s%i%s\n", cwd, " - #chdir", status, ")"); /*para ver se esta certo*/
	}
    else //executa quando a flag eh negativa
	{
        printf("%s\n", "Error, you need a correct parameter");
		return;
    }
	change_or_add_value(data.dict, "PWD",  getcwd(cwd, sizeof(cwd)));
}
