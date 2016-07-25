/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_history.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/07 19:21:51 by pbourrie          #+#    #+#             */
/*   Updated: 2016/07/25 00:59:32 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	history_print(t_env *e)
{
	t_histo	*cur;
	int		i;
	int		fd;

	i = 1;
	fd = e->cmd[e->cid].fd_out;
	cur = e->histo_begin;
	while (cur)
	{
		ft_putnchar_fd((ft_nbrlen(e->histo_size) - ft_nbrlen(i)) + 1, ' ', fd);
		ft_putnbr_fd(i, fd);
		ft_putstr_fd("  ", fd);
		ft_putendl_fd(cur->line, fd);
		cur = cur->down;
		i++;
	}
}
