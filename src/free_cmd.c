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
	int	j;

	i = 0;
	while (e->cmd_seq[i])
	{
		j = 0;
		while (e->cmd_seq[i][j])
		{
			free(e->cmd_seq[i][j]);
			e->cmd_seq[i][j] = NULL;
			j++;
		}
		free(e->cmd_seq[i]);
		e->cmd_seq[i] = NULL;
		i++;
	}
	free(e->cmd_seq);
	e->cmd_seq = NULL;
	e->cmd = NULL;
	free(e->usr_cmd);
	e->usr_cmd = NULL;
}
