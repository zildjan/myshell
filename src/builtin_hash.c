/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_hash.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/27 17:19:41 by pbourrie          #+#    #+#             */
/*   Updated: 2016/01/28 01:17:36 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void		builtin_hash(t_env *e)
{
	char	opt_r;
	char	opt_s;
	int		i;

	if ((i = builtin_hash_get_opt(e, &opt_r, &opt_s)) == -1)
	{
		e->status = 1;
		put_cmd_opt_error("hash", 1, e->cmd[e->cid].fd_err, "[-rs] [utility...]");
		return ;
	}
	e->status = 0;
	if (opt_r)
	{
		free_hash_table(e);
		e->hash_size = 0;
		e->hash_total = 3;
		e->hash_t = (t_hash_b**)ft_memalloc(sizeof(t_hash_b*) * e->hash_total);
	}
	builtin_hash_print(e, opt_s);
}

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
	int		i;

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
	ft_putstr_fd("Collisions Stats:\n", e->cmd[e->cid].fd_out);
	i = 0;
	while (++i <= stats->col_max + 1 && i <199 && e->hash_size)
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

t_hash_stat	*builtin_hash_load(t_env *e)
{
	int			i;
	int			i2;
	t_hash_stat	*stats;
	int			nb;
	t_hash_b	*tmp;

	stats = (t_hash_stat*)ft_memalloc(sizeof(t_hash_stat));
	stats->col = (int*)ft_memalloc(sizeof(int) * 200);
	stats->stab = (char**)ft_memalloc(sizeof(char*) * (e->hash_size + 1));
	stats->col_max = 0;
	i = -1;
	i2 = 0;
	while (++i < e->hash_total)
	{
		tmp = e->hash_t[i];
		nb = 0;
		while (tmp)
		{
			stats->stab[i2] = ft_strnew(ft_strlen(tmp->key) + ft_strlen(tmp->val) + 1);
			ft_strcpy(stats->stab[i2], tmp->key);
			ft_strcat(stats->stab[i2], "=");
			ft_strcat(stats->stab[i2++], tmp->val);
			tmp = tmp->next;
			if (nb > stats->col_max)
				stats->col_max = nb;
			nb++;
		}
		if (e->hash_t[i])
			stats->col[nb]++;
	}
	stats->stab[i2] = NULL;
	myqsort(stats->stab, 0, i2 - 1);
	return (stats);
}

int		builtin_hash_get_opt(t_env *e, char *opt_r, char *opt_s)
{
	int		i;
	int		i2;

	*opt_r = 0;
	*opt_s = 0;
	i = 0;
	while (e->carg[++i])
	{
		i2 = 0;
		if (e->carg[i][i2] == '-')
			while (e->carg[i][++i2] && i2 > 0)
			{
				if (e->carg[i][i2] == 'r')
					*opt_r = 1;
				else if (e->carg[i][i2] == 's')
					*opt_s = 1;
				else
					return (-1);
			}
		if (i2 <= 1)
			break ;
	}
	return (i);
}
