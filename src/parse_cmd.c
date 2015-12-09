/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/09 19:55:32 by pbourrie          #+#    #+#             */
/*   Updated: 2015/11/12 21:46:48 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	parse_cmd(t_env *e)
{
	int		i;
	t_parse	p;

	e->cid = 0;
	p.a_id = 0;
	e->nb_cmd = 1;
	p.quo = NONE;
	p.bslash = 0;
	p.buf = ft_strnew(500);
//	ft_strclr(p.buf);
	i = -1;
	p.ib = 0;
	e->cmd = (t_cmd*)ft_memalloc(sizeof(t_cmd) * (e->nb_cmd));

	while (e->line[++i])
	{
		if (e->line[i] == '\'' && (!p.quo || p.quo == SIMP))
		{
			if (p.quo)
				parse_add_arg(e, &p);
			else
				p.quo = SIMP;
		}
		else if (e->line[i] == '"' && (!p.quo || p.quo == DOUB))
		{
			if (p.quo)
				parse_add_arg(e, &p);
			else
				p.quo = DOUB;
		}
		else if (e->line[i] == ' ' && !p.quo)
		{
			parse_add_arg(e, &p);
		}
		else
		{
			p.buf[p.ib++] = e->line[i];
//			ft_printf("'%c' = '%s'\n", p.buf[p.ib - 1], p.buf);
		}
	}
	if (p.ib)
		parse_add_arg(e, &p);

	free(p.buf);
	e->cmd[e->cid].arg[p.a_id] = NULL;
	e->cid = 0;
	ft_printf("'%s' %ld\n", e->cmd[0].arg[0], e->cmd[0].quo[0]);
//	if (e->cmd[0].arg[0] == NULL)
//		return ;
//	parse_cmd_args(e);
	process_cmd(e);
	free_cmd(e);
}

void	parse_add_arg(t_env *e, t_parse *p)
{
	int		old_size;
	int		new_size;
	int		old_isize;
	int		new_isize;
	char	***parg;
	char	**pquo;

	old_size = sizeof(char*) * (p->a_id);
	new_size = sizeof(char*) * (p->a_id + 1);
	old_isize = sizeof(char) * (p->a_id);
	new_isize = sizeof(char) * (p->a_id + 1);
	parg = &e->cmd[e->cid].arg;
	pquo = &e->cmd[e->cid].quo;
	if (p->a_id == 0)
	{
		*parg = (char**)ft_memalloc(new_size);
		*pquo = (char*)ft_memalloc(new_isize);
	}
	else
	{
		
		*parg = (char**)ft_memrealloc(*parg, old_size, new_size);
		*pquo = (char*)ft_memrealloc(*pquo, old_isize, new_isize);
	}

	e->cmd[e->cid].arg[p->a_id] = ft_strdup(p->buf);
	e->cmd[e->cid].arg[p->a_id + 1] = NULL;
	e->cmd[e->cid].quo[p->a_id] = p->quo;
	ft_strclr(p->buf);
//	ft_bzero(p->buf, 500);
	p->ib = 0;
	p->quo = NONE;
	p->a_id++;

//	ft_printf("ICI\n");
}



void	parse_cmd_args(t_env *e)
{
	int	i;
	int	i2;

	i = 0;
	i2 = 0;
	while (e->nb_cmd > i )
	{
		while (e->cmd[i].arg[i2])
		{
			parse_env_var(e, i, i2);
			parse_home_tilde(e, i, i2);
			i2++;
		}
		i2 = 0;
		i++;
	}
}

/*
void	parse_redirections(t_env *e)
{
	int		i;
	int		i2;
	char	**cmds;

	i = -1;
	i2 = 0;
	while (cmds[++i])
	{
		while (cmds[i][i2])
		{
			if (cmds[i][i2] == '>' || cmds[i][i2] == '<')
				i2++;
		}
		i2 = 0;
	}
}
*/

