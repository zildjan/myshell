/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/09 19:55:32 by pbourrie          #+#    #+#             */
/*   Updated: 2015/10/09 21:27:14 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	builtin_exit(t_env *e)
{
	if (e->cmd)
	{
		if (e->cmd[1] && e->cmd[2])
			ft_putendl_fd("exit: too many arguments", 2);
		else if (e->cmd[1])
		{
			if (ft_strcheck(e->cmd[1], ft_isdigit))
				exit(ft_atoi(e->cmd[1]));
			else
				ft_putendl_fd("exit: syntax error", 2);
		}
		else
			exit(e->last_exit);
	}
	else
		exit(e->last_exit);
}
