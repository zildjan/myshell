/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/09 19:55:32 by pbourrie          #+#    #+#             */
/*   Updated: 2015/11/12 18:58:52 by pbourrie         ###   ########.fr       */
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
				builtin_exit_jobs(e, ft_atoi(e->carg[1]));
			else
				builtin_exit_jobs(e, 0);
		}
		else
			builtin_exit_jobs(e, e->status);
	}
	else
		builtin_exit_jobs(e, e->status);
}

void	builtin_exit_jobs(t_env *e, int status)
{
	jobs_exit(e);
	exit(status);
}
