/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/09 19:55:32 by pbourrie          #+#    #+#             */
/*   Updated: 2015/11/12 21:46:48 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	parse_cmd(t_env *e)
{
	if (e->cmd[0].arg[0] == NULL)
		return ;
	parse_cmd_args(e);
	process_cmd(e);
}

void	parse_cmd_args(t_env *e)
{
	int	i;
	int	i2;

	i = 0;
	i2 = 0;
	while (e->nb_cmd > i )
	{
		while (e->cmd[i].arg[i2])
		{
			parse_env_var(e, i, i2);
			parse_home_tilde(e, i, i2);
			i2++;
		}
		i2 = 0;
		i++;
	}
}

/*
void	parse_redirections(t_env *e)
{
	int		i;
	int		i2;
	char	**cmds;

	i = -1;
	i2 = 0;
	while (cmds[++i])
	{
		while (cmds[i][i2])
		{
			if (cmds[i][i2] == '>' || cmds[i][i2] == '<')
				i2++;
		}
		i2 = 0;
	}
}
*/

