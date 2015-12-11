/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/09 19:55:32 by pbourrie          #+#    #+#             */
/*   Updated: 2015/10/09 21:27:14 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	free_cmd(t_env *e)
{
	int	i;
	int	i2;

	i = 0;
	i2 = 0;
	while (e->nb_cmd > i)
	{
		while (e->cmd[i].arg[i2])
		{
			free(e->cmd[i].arg[i2]);
			e->cmd[i].arg[i2] = NULL;
			i2++;
		}
		free(e->cmd[i].arg);
		free(e->cmd[i].quo);
		if (e->cmd[i].in)
			free(e->cmd[i].in);
		if (e->cmd[i].out)
			free(e->cmd[i].out);
		e->cmd[i].arg = NULL;
		i2 = 0;
		i++;
	}
	free(e->cmd);
	e->cmd = NULL;
}
