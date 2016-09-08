/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/09 00:37:42 by pbourrie          #+#    #+#             */
/*   Updated: 2016/09/09 00:38:09 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	parse_init(t_env *e, t_parse *p)
{
	p->quo = NONE;
	p->quoted = NONE;
	p->doalias = 0;
	p->aliased = 0;
	p->bquo = NONE;
	p->escape = 0;
	p->sub = 0;
	p->separ = 0;
	p->redirec = NONE;
	p->error = 0;
	p->buf_len = p->line_len;
	p->buf = ft_strnew(p->buf_len);
	p->i = -1;
	p->last_i = 0;
	p->ib = 0;
	p->ignore = 0;
	parse_init_cmd(e, p);
}

void	parse_init_cmd(t_env *e, t_parse *p)
{
	e->cid = 0;
	p->a_id = 0;
	e->nb_cmd = 1;
	e->background_cmd = 0;
	e->cmd = (t_cmd*)ft_memalloc(sizeof(t_cmd) * (e->nb_cmd));
	e->cmd[0].redir = NULL;
	e->cmd[0].hdoc = NULL;
	e->cmd[0].condi = 0;
	e->cmd[0].fd_in = 0;
	e->cmd[0].fd_out = 1;
	e->cmd[0].fd_err = 2;
	p->last_i = p->i + 1;
}
