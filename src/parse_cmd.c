/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/09 19:55:32 by pbourrie          #+#    #+#             */
/*   Updated: 2015/11/10 18:59:26 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	parse_cmd(t_env *e)
{
	if (e->cmd[0] == NULL)
		return ;
	parse_cmd_args(e);
	if (!process_builtin(e))
		process_cmd(e);
}

void	parse_cmd_args(t_env *e)
{
	int	i;

	i = 0;
	while (e->cmd[i])
	{
		parse_env_var(e, i);
		parse_home_tilde(e, i);
		i++;
	}
}

