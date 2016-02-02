/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/01 22:42:57 by pbourrie          #+#    #+#             */
/*   Updated: 2016/02/02 01:43:01 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

t_poss	*completion_get_poss(t_env *e, int type)
{
	t_poss	*poss;
	char	*start;

	start = completion_get_start(e);
	poss = completion_find_poss(e, type, start);
	free(start);
	return (poss);
}

char	*completion_get_start(t_env *e)
{
	int		start;

	start = 0;
	if (e->cur)
		start = e->cur - 1;
	while (start && !is_aspace(e->line[start]))
		start--;
	if (is_aspace(e->line[start]))
		start++;
	return (ft_strsub(e->line, start, e->cur - start));
}

t_poss	*completion_find_poss(t_env *e, int type, char *start)
{
	t_poss	*poss;

	poss = NULL;
	if (!type)
	{
		int		i;
		t_hash_b	*tmp;

		i = -1;
		while (++i < e->hash_total)
		{
			tmp = e->hash_t[i];
			while (tmp)
			{
				if (ft_strnequ(start, tmp->key, ft_strlen(start)))
					completion_addtoposs(&poss, tmp->key);
				tmp = tmp->next;
			}
		}
	}
	return (poss);
}

void	completion_addtoposs(t_poss **poss, char *str)
{
	t_poss	*cur;
	t_poss	*new;

	new = (t_poss*)ft_memalloc(sizeof(t_poss));
	new->str = str;
	if (!*poss)
		*poss = new;
	else
	{
		cur = *poss;
		while (cur->next)
			cur = cur->next;
		cur->next = new;
	}
}
