/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/07 23:28:08 by pbourrie          #+#    #+#             */
/*   Updated: 2016/02/07 23:45:43 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	builtin_echo(t_env *e)
{
	int		i;
	int		no_new_line;

	e->status = 0;
	i = 0;
	no_new_line = 0;
	if (ft_strequ(e->cmd[e->cid].arg[1], "-n"))
		no_new_line = ++i;
	while (e->cmd[e->cid].arg[++i])
	{
		if (i - no_new_line > 1)
			ft_putchar_fd(' ', e->cmd[e->cid].fd_out);
		ft_putstr_fd(e->cmd[e->cid].arg[i], e->cmd[e->cid].fd_out);
	}
	if (!no_new_line)
		ft_putchar_fd('\n', e->cmd[e->cid].fd_out);
}
