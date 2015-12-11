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
	t_parse	p;

	p.line_len = ft_strlen(e->line);
	if (p.line_len > 1000)
	{
		return ;
		ft_putendl_fd("input line too long", 2);
	}
	parse_cmd_cleanline(e);
	e->cid = 0;
	p.a_id = 0;
	e->nb_cmd = 1;
	p.quo = NONE;
	p.redirec = NONE;
	p.error = 0;
	p.buf = ft_strnew(ft_strlen(e->line));

	p.i = -1;
	p.ib = 0;
	e->cmd = (t_cmd*)ft_memalloc(sizeof(t_cmd) * (e->nb_cmd));
	e->cmd[0].pipe_in = 0;
	e->cmd[0].pipe_out = 0;
	e->cmd[0].in_t = NONE;
	e->cmd[0].out_t = NONE;

	while (e->line[++p.i] && !p.error)
	{
		if (e->line[p.i] == '\'' && (!p.quo || p.quo == SIMP)
			&& e->line[p.i - 1] != '\\')
		{
			if (p.quo)
				parse_add_arg(e, &p);
			else
				p.quo = SIMP;
		}
		else if (e->line[p.i] == '"' && (!p.quo || p.quo == DOUB)
				 && e->line[p.i - 1] != '\\')
		{
			if (p.quo)
				parse_add_arg(e, &p);
			else
				p.quo = DOUB;
		}
		else if (e->line[p.i] == '|' && !p.quo
				 && e->line[p.i - 1] != '\\')
		{
			if (e->line[p.i - 1] != ' ' && p.ib > 0)
				parse_add_arg(e, &p);
			if (p.a_id == 0)
			{
				p.error = EP_NULL_CMD;
				break ;
			}
			parse_add_cmd(e, &p, 1);
			if (e->line[p.i + 1] == ' ')
				p.i++;

		}
		else if (e->line[p.i] == ';' && !p.quo
				 && e->line[p.i - 1] != '\\')
		{
			if (e->line[p.i - 1] != ' ' && p.ib > 0)
				parse_add_arg(e, &p);
			if (p.a_id)
				parse_add_cmd(e, &p, 0);
			if (e->line[p.i + 1] == ' ')
				p.i++;

		}
		else if ((e->line[p.i] == '<' || e->line[p.i] == '>')
				 && !p.quo && e->line[p.i - 1] != '\\')
		{
			parse_get_redirec_type(e, &p);
		}
		else if (e->line[p.i] == ' ' && !p.quo
				 && e->line[p.i - 1] != '\\')
		{
			if (e->line[p.i - 1] != ' ')
				parse_add_arg(e, &p);
		}
		else
		{
			if (e->line[p.i - 1] == '\\' 
				&& ((e->line[p.i] == '\'' && p.quo == SIMP)
					|| (e->line[p.i] == '"' && p.quo == DOUB)
					|| (e->line[p.i] == ' ' && p.quo == NONE)))
				p.ib--;
			if (!(e->line[p.i] == '\\'
				  && p.quo == NONE && e->line[p.i + 1] != ' '))
				p.buf[p.ib++] = e->line[p.i];
//			ft_printf("'%c' = '%s'\n", p.buf[p.ib - 1], p.buf);
		}

	}

	if (p.ib)
		parse_add_arg(e, &p);
	else
	{
		if (!e->cid && !p.a_id)
		{
			free(p.buf);
			free(e->cmd);
			return ;
		}
	}
	if (p.a_id == 0)
		e->nb_cmd--;
	if (p.redirec)
		p.error = EP_MISS_REDIREC;
// */

//	p.error = 1;

	if (p.error)
	{
		if (p.error == EP_NULL_CMD)
			ft_putendl_fd("Invalid null command.", 2);
		else if (p.error == EP_AMB_OUT)
			ft_putendl_fd("Ambiguous output redirect.", 2);
		else if (p.error == EP_AMB_IN)
			ft_putendl_fd("Ambiguous input redirect.", 2);
		else if (p.error == EP_MISS_REDIREC)
			ft_putendl_fd("Missing name for redirect.", 2);
	}

	free(p.buf);
	e->cid = 0;
//	ft_printf("'%s' %ld\n", e->cmd[0].arg[0], e->cmd[0].quo[0]);
//	if (e->cmd[0].arg[0] == NULL)
//		return ;
	if (!p.error)
	{
		parse_cmd_args(e);
		process_cmd(e);
	}
	free_cmd(e);
}

void	parse_add_cmd(t_env *e, t_parse *p, char pipe)
{
	int		old_size;
	int		new_size;

//	ft_printf("NEW CMD\n");

	if (p->redirec)
		p->error = EP_MISS_REDIREC;

	old_size = sizeof(t_cmd) * (e->nb_cmd);
	new_size = sizeof(t_cmd) * (e->nb_cmd + 1);
	e->cmd = (t_cmd*)ft_memrealloc(e->cmd, old_size, new_size);

	e->nb_cmd++;
	e->cid++;
	p->a_id = 0;
	e->cmd[e->cid].pipe_in = 0;
	e->cmd[e->cid].pipe_out = 0;
	e->cmd[e->cid].in_t = NONE;
	e->cmd[e->cid].out_t = NONE;
	e->cmd[e->cid].in = NULL;
	e->cmd[e->cid].out = NULL;

	if (pipe && e->cmd[e->cid - 1].out_t)
	{
		p->error = EP_AMB_OUT;
	}
	if (pipe)
	{
		e->cmd[e->cid].in_t = R_PIPE;
		e->cmd[e->cid - 1].out_t = R_PIPE;
		e->cmd[e->cid].pipe_in = 1;
		e->cmd[e->cid - 1].pipe_out = 1;
	}

//	ft_printf("ICI\n");
}

void	parse_add_arg(t_env *e, t_parse *p)
{
	int		old_size;
	int		new_size;
	int		old_isize;
	int		new_isize;
	char	***parg;
	char	**pquo;

	if (p->redirec)
	{
		parse_add_redirec(e, p);
		return ;
	}

//	ft_printf("NEW ARG\n");

	old_size = sizeof(char*) * (p->a_id + 1);
	new_size = sizeof(char*) * (p->a_id + 2);
	old_isize = sizeof(char) * (p->a_id + 1);
	new_isize = sizeof(char) * (p->a_id + 2);
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

//	ft_printf("->'%s' %ld '%ld'\n", p->buf, ft_strlen(p->buf), p->buf[ft_strlen(p->buf)]);
	e->cmd[e->cid].arg[p->a_id] = ft_strdup(p->buf);
	e->cmd[e->cid].arg[p->a_id + 1] = NULL;
	e->cmd[e->cid].quo[p->a_id] = p->quo;
	ft_strclr(p->buf);
	p->ib = 0;
	p->quo = NONE;
	p->a_id++;

//	ft_printf("ICI\n");
}

int		parse_add_redirec(t_env *e, t_parse *p)
{
	if (!p->ib)
		return (p->error = EP_MISS_REDIREC);
//	ft_printf("NEW REDIREC -> '%s'\n", p->buf);
	if (p->redirec == R_OUTA || p->redirec == R_OUT)
	{
		if (e->cmd[e->cid].out_t)
			return (p->error = EP_AMB_OUT);
		e->cmd[e->cid].out = ft_strdup(p->buf);
		e->cmd[e->cid].out_t = p->redirec;
	}
	else
	{
		if (e->cmd[e->cid].in_t)
			return (p->error = EP_AMB_IN);
		e->cmd[e->cid].in = ft_strdup(p->buf);
		e->cmd[e->cid].in_t = p->redirec;
	}
	ft_strclr(p->buf);
	p->ib = 0;
	p->quo = NONE;
	p->redirec = NONE;
	return (0);
}

void	parse_get_redirec_type(t_env *e, t_parse *p)
{
	if (p->redirec)
		p->error = EP_MISS_REDIREC;
	if (e->line[p->i] == '>' && e->line[p->i + 1] != '>')
	{
		p->redirec = R_OUT;
	}
	else if (e->line[p->i] == '>' && e->line[p->i + 1] == '>')
	{
		p->redirec = R_OUTA;
		p->i++;
	}
	else if (e->line[p->i] == '<' && e->line[p->i + 1] != '<')
	{
		p->redirec = R_IN;
	}
	else if (e->line[p->i] == '<' && e->line[p->i + 1] == '<')
	{
		p->redirec = R_HDOC;
		p->i++;
	}
	while (e->line[p->i + 1] == ' ')
		p->i++;
//	ft_printf("->'%s'\n", e->line + p->i);
}

void	parse_cmd_cleanline(t_env *e)
{
	int		start;
	int		len;
	char	*temp;

//	ft_printf("line = '%s'\n", e->line);
	start = 0;
	while (e->line[start] && e->line[start] == ' ')
		start++;
	len = ft_strlen(e->line) - 1;
	while (len > 0 && e->line[len] == ' ')
		len--;
	temp = ft_strsub(e->line, start, len - start + 1);
	free(e->line);
	e->line = temp;
//	ft_printf("line = '%s'\n", e->line);
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
			if (e->cmd[i].quo[i2] != SIMP)
				parse_env_var(e, i, i2);
			if (!e->cmd[i].quo[i2])
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

