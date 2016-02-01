/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_hash_print.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/01 01:36:29 by pbourrie          #+#    #+#             */
/*   Updated: 2016/02/01 01:37:24 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void		builtin_hash_print(t_env *e, char opt_s)
{
	int			i;
	t_hash_stat	*stats;

	stats = builtin_hash_load(e);
	i = -1;
	while (stats->stab[++i])
	{
		if (!opt_s)
			ft_putendl_fd(stats->stab[i], e->cmd[e->cid].fd_out);
		free(stats->stab[i]);
	}
	if (opt_s)
		builtin_hash_print_stats(e, stats);
	free(stats->col);
	free(stats->stab);
	free(stats);
}

void		builtin_hash_print_stats(t_env *e, t_hash_stat *stats)
{
	double	nb;
	char	*str;

	ft_putnbr_fd(e->hash_size, e->cmd[e->cid].fd_out);
	ft_putstr_fd(" / ", e->cmd[e->cid].fd_out);
	ft_putnbr_fd(e->hash_total, e->cmd[e->cid].fd_out);
	ft_putendl_fd(" Buckets", e->cmd[e->cid].fd_out);
	nb = (((double)e->hash_total - e->hash_size) * 100) / (double)e->hash_total;
	str = ft_dtoa(nb, 2);
	ft_putstr_fd("Table empty space: ", e->cmd[e->cid].fd_out);
	ft_putstr_fd(str, e->cmd[e->cid].fd_out);
	ft_putendl_fd("%", e->cmd[e->cid].fd_out);
	free(str);
	builtin_hash_print_colstats(e, stats);
}

void		builtin_hash_print_colstats(t_env *e, t_hash_stat *stats)
{
	double	nb;
	char	*str;
	int		i;

	ft_putstr_fd("Collisions Stats:\n", e->cmd[e->cid].fd_out);
	i = 0;
	while (++i <= stats->col_max + 1 && i < 199 && e->hash_size)
	{
		nb = ((double)stats->col[i] * i * 100) / (double)e->hash_size;
		str = ft_dtoa(nb, 2);
		ft_putstr_fd(" ", e->cmd[e->cid].fd_out);
		ft_putnbr_fd(i - 1, e->cmd[e->cid].fd_out);
		ft_putstr_fd(" -> ", e->cmd[e->cid].fd_out);
		if (nb < 10)
			ft_putchar_fd(' ', e->cmd[e->cid].fd_out);
		ft_putstr_fd(str, e->cmd[e->cid].fd_out);
		ft_putendl_fd("%", e->cmd[e->cid].fd_out);
		free(str);
	}
}
