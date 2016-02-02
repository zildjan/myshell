/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/01 21:57:23 by pbourrie          #+#    #+#             */
/*   Updated: 2016/02/01 21:57:52 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	hash_table_resize(t_env *e)
{
	t_hash_b	**old_table;
	int			old_total;

	if (e->hash_size * 2 < e->hash_total)
		return ;
	old_total = e->hash_total;
	e->hash_total = (e->hash_size * 2) + 263;
	old_table = e->hash_t;
	e->hash_size = 0;
	e->hash_t = (t_hash_b**)ft_memalloc(sizeof(t_hash_b*) * e->hash_total);
	hash_table_rebuilt(e, old_table, old_total);
}

void	hash_table_rebuilt(t_env *e, t_hash_b **old_table, int old_total)
{
	int			i;
	t_hash_b	*cur;
	t_hash_b	*tmp;

	i = -1;
	while (++i < old_total)
	{
		cur = old_table[i];
		while (cur)
		{
			hash_add(e, cur->key, cur->val);
			tmp = cur;
			cur = cur->next;
			free(tmp->key);
			free(tmp->val);
			free(tmp);
		}
	}
	free(old_table);
}
