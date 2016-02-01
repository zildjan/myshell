/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_hash.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/27 17:19:41 by pbourrie          #+#    #+#             */
/*   Updated: 2016/02/01 01:37:22 by pbourrie         ###   ########.fr       */
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
		put_cmd_opt_error("hash", 1, e->cmd[e->cid].fd_err, "[-rs]");
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

t_hash_stat	*builtin_hash_load(t_env *e)
{
	t_hash_stat	*stats;

	stats = (t_hash_stat*)ft_memalloc(sizeof(t_hash_stat));
	stats->col = (int*)ft_memalloc(sizeof(int) * 200);
	stats->stab = (char**)ft_memalloc(sizeof(char*) * (e->hash_size + 1));
	stats->col_max = 0;
	stats->i = -1;
	stats->i2 = 0;
	while (++stats->i < e->hash_total)
	{
		builtin_hash_load2(e, stats, e->hash_t[stats->i]);
	}
	stats->stab[stats->i2] = NULL;
	myqsort(stats->stab, 0, stats->i2 - 1);
	return (stats);
}

void		builtin_hash_load2(t_env *e, t_hash_stat *stats, t_hash_b *tmp)
{
	int			nb;
	int			len;

	nb = 0;
	while (tmp)
	{
		len = ft_strlen(tmp->key) + ft_strlen(tmp->val) + 1;
		stats->stab[stats->i2] = ft_strnew(len);
		ft_strcpy(stats->stab[stats->i2], tmp->key);
		ft_strcat(stats->stab[stats->i2], "=");
		ft_strcat(stats->stab[stats->i2++], tmp->val);
		tmp = tmp->next;
		if (nb > stats->col_max)
			stats->col_max = nb;
		nb++;
	}
	if (e->hash_t[stats->i])
		stats->col[nb]++;
}

int			builtin_hash_get_opt(t_env *e, char *opt_r, char *opt_s)
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
