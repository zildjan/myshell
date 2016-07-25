/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/01 22:42:57 by pbourrie          #+#    #+#             */
/*   Updated: 2016/07/26 00:19:03 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	completion_update(t_env *e)
{
	char	*start;
	t_parse	lex;

	lexer(e, &lex, e->cur);
	if (e->compl)
	{
		if (ft_strequ(lex.buf, e->compl->start) && lex.i == e->compl->lex.i)
		{
			free(lex.buf);
			return ;
		}
	}
	completion_free(e);
	start = ft_strdup(lex.buf);
	e->compl = (t_compl*)ft_memalloc(sizeof(t_compl));
	e->compl->total = 3;
	e->compl->poss = (char**)ft_memalloc(sizeof(char*) * e->compl->total);
	e->compl->start = start;
	e->compl->cur = -1;
	e->compl->lex = lex;
	completion_get_poss(e);
	myqsort(e->compl->poss, 0, e->compl->size - 1);
	completion_check_mutual(e);
}

void	completion_addtoposs(t_env *e, char *str)
{
	int		old_s;
	int		new_s;
	int		i;

	i = -1;
	while (e->compl->poss[++i])
		if (ft_strequ(str, e->compl->poss[i]))
			return ;
	e->compl->poss[e->compl->size++] = ft_strdup(str);
	i = ft_strlen(str);
	if (i > e->compl->len_max)
		e->compl->len_max = i;
	if (e->compl->size + 10 > e->compl->total)
	{
		old_s = sizeof(char*) * e->compl->total;
		e->compl->total += 100;
		new_s = sizeof(char*) * e->compl->total;
		e->compl->poss = (char**)ft_memrealloc(e->compl->poss, old_s, new_s);
	}
	e->compl->poss[e->compl->size] = NULL;
}

void	completion_check_mutual(t_env *e)
{
	int		i;
	int		i2;

	if (!e->compl->size)
		return ;
	e->compl->mutual = ft_strdup(e->compl->poss[0]);
	i = 0;
	while (e->compl->poss[++i])
	{
		i2 = 0;
		while (e->compl->poss[i][i2] == e->compl->mutual[i2])
			i2++;
		e->compl->mutual[i2] = 0;
	}
}

void	completion_free(t_env *e)
{
	int		i;

	if (!e->compl)
		return ;
	i = -1;
	while (e->compl->poss[++i])
		free(e->compl->poss[i]);
	free(e->compl->poss);
	free(e->compl->start);
	free(e->compl->cstart);
	if (e->compl->mutual)
		free(e->compl->mutual);
	if (e->compl->path)
		free(e->compl->path);
	if (e->compl->lex.buf)
		free(e->compl->lex.buf);
	free(e->compl);
	e->compl = NULL;
}
