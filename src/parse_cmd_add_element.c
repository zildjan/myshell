/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_add_element.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 17:06:44 by pbourrie          #+#    #+#             */
/*   Updated: 2016/05/24 21:15:40 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	parse_add_cmd(t_env *e, t_parse *p, char sep)
{
	int		old_size;
	int		new_size;

	if (p->redirec)
		p->error = EP_MISS_REDIREC;
	if (p->a_id == 0)
		p->error = EP_NULL_CMD;
	old_size = sizeof(t_cmd) * (e->nb_cmd);
	new_size = sizeof(t_cmd) * (e->nb_cmd + 1);
	e->cmd = (t_cmd*)ft_memrealloc(e->cmd, old_size, new_size);
	e->nb_cmd++;
	e->cid++;
	p->a_id = 0;
	e->cmd[e->cid].fd_in = 0;
	e->cmd[e->cid].fd_out = 1;
	e->cmd[e->cid].fd_err = 2;
	e->cmd[e->cid].condi = NONE;
	e->cmd[e->cid].redir = NULL;
	e->cmd[e->cid].hdoc = NULL;
	set_env_var(e, "_", p->last_arg);
	parse_add_cmd_sep(e, p, sep);
}

void	parse_add_arg(t_env *e, t_parse *p)
{
	int		old_size;
	int		new_size;
	char	***parg;

	if (p->redirec)
	{
		parse_add_redirec(e, p);
		return ;
	}
	old_size = sizeof(char*) * (p->a_id + 1);
	new_size = sizeof(char*) * (p->a_id + 2);
	parg = &e->cmd[e->cid].arg;
	if (p->a_id == 0)
		*parg = (char**)ft_memalloc(new_size);
	else
		*parg = (char**)ft_memrealloc(*parg, old_size, new_size);
	e->cmd[e->cid].arg[p->a_id] = dup_arg(p->buf);
	if (p->a_id == 0)
		p->last_arg = e->cmd[e->cid].arg[p->a_id];
	e->cmd[e->cid].arg[p->a_id + 1] = NULL;
	ft_strclr(p->buf);
	p->ib = 0;
	p->quo = NONE;
	p->a_id++;
}

void	parse_add_cmd_sep(t_env *e, t_parse *p, char sep)
{
	p->separ = sep;
	if (sep == SEP_PIPE)
	{
		e->cmd[e->cid].condi = SEP_PIPE;
		new_redirec(e, NULL, R_PIPEIN, 0);
		e->cid--;
		new_redirec(e, NULL, R_PIPEOUT, 1);
		e->cid++;
	}
	else if (sep == SEP_AND)
		e->cmd[e->cid].condi = SEP_AND;
	else if (sep == SEP_OR)
		e->cmd[e->cid].condi = SEP_OR;
}
