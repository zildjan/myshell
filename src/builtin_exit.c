/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/09 19:55:32 by pbourrie          #+#    #+#             */
/*   Updated: 2016/05/28 00:44:33 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	builtin_exit(t_env *e)
{
	if (e->carg)
	{
		if (e->carg[1] && e->carg[2])
			ft_putendl_fd("exit: too many arguments", e->cmd[e->cid].fd_err);
		else if (e->carg[1])
		{
			if (ft_strcheck(e->carg[1], ft_isdigit))
				builtin_exit_all(e, ft_atoi(e->carg[1]));
			else
				builtin_exit_all(e, 0);
		}
		else
			builtin_exit_all(e, e->status);
	}
	else
		builtin_exit_all(e, e->status);
}

void	builtin_exit_all(t_env *e, int status)
{
	kill_jobs(e);
	term_restore_backup(NULL);
	free_env(e);
//	while (1)
//		sleep(2);
	exit(status);
}
