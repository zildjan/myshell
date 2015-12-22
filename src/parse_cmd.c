/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/09 19:55:32 by pbourrie          #+#    #+#             */
/*   Updated: 2015/12/17 21:48:35 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	parse_cmd(t_env *e)
{
	t_parse	p;

	parse_cmd_cleanline(e);
	p.line_len = ft_strlen(e->line);
	if (p.line_len > 1200)
	{
		ft_putendl_fd("input line too long", 2);
		return ;
	}
	if (!p.line_len)
		return ;
	e->cid = 0;
	p.a_id = 0;
	e->nb_cmd = 1;
	p.quo = NONE;
	p.escape = 0;
	p.separ = 0;
	p.last_arg = NULL;
	p.redirec = NONE;
	p.error = 0;
	p.buf = ft_strnew(p.line_len);

	p.i = -1;
	p.ib = 0;
	e->cmd = (t_cmd*)ft_memalloc(sizeof(t_cmd) * (e->nb_cmd));
	e->cmd[0].redir = NULL;
	e->cmd[0].hdoc = NULL;
	e->cmd[0].condi = 0;
	e->cmd[0].fd_in = 0;
	e->cmd[0].fd_out = 1;
	e->cmd[0].fd_err = 2;

	while (1)
	{
		if (p.error)
			break ;
		if (!e->line[++p.i])
		{
			if (p.ib)
				parse_add_arg(e, &p);
			if (p.quo == SIMP)
				get_cmd_end(e, '\'');
			else if (p.quo == DOUB)
				get_cmd_end(e, '"');
			else if (p.escape)
				get_cmd_end(e, 0);
			else if (!p.a_id && p.separ)
				get_cmd_end(e, p.separ);
			else
				break ;
			p.i = 0;
			p.escape = 0;
			parse_cmd_cleanline(e);
			p.line_len = ft_strlen(e->line);
			if (p.line_len > 1000 || !p.line_len)
				break ;
			free(p.buf);
			p.buf = ft_strnew(ft_strlen(e->line));
		}
//		ft_printf("STA i=%ld c='%c'\n", p.i, e->line[p.i]);

		if (e->line[p.i] == '\'' && (!p.quo || p.quo == SIMP)
			&& !p.escape)
		{
			if (p.quo)
				p.quo = NONE;
			else
				p.quo = SIMP;
		}
		else if (e->line[p.i] == '"' && (!p.quo || p.quo == DOUB)
				 && !p.escape)
		{
			if (p.quo)
				p.quo = NONE;
			else
				p.quo = DOUB;
		}
		else if (e->line[p.i] == '&' && e->line[p.i + 1] == '&'
				 && !p.quo && !p.escape)
		{
			p.i++;
			if (p.ib > 0)
				parse_add_arg(e, &p);
			if (p.a_id == 0)
			{
				p.error = EP_NULL_CMD;
				break ;
			}
			parse_add_cmd(e, &p, SEP_AND);
		}
		else if (e->line[p.i] == '|' && e->line[p.i + 1] == '|'
				 && !p.quo && !p.escape)
		{
			p.i++;
			if (p.ib > 0)
				parse_add_arg(e, &p);
			if (p.a_id == 0)
			{
				p.error = EP_NULL_CMD;
				break ;
			}
			parse_add_cmd(e, &p, SEP_OR);
		}
		else if (e->line[p.i] == '|' && !p.quo
				 && !p.escape)
		{
			if (p.ib > 0)
				parse_add_arg(e, &p);
			if (p.a_id == 0)
			{
				p.error = EP_NULL_CMD;
				break ;
			}
			parse_add_cmd(e, &p, SEP_PIPE);
		}
		else if (e->line[p.i] == ';' && !p.quo
				&& !p.escape)
		{
			if (p.ib > 0)
				parse_add_arg(e, &p);
			if (p.a_id)
				parse_add_cmd(e, &p, NONE);
		}
		else if (e->line[p.i] == '$' && p.quo !=SIMP
				&& !p.escape)
		{
			parse_var_expansion(e, &p);
		}
		else if (e->line[p.i] == '~' && !p.quo && !p.ib
				&& !p.escape)
		{
			parse_tilde_expansion(e, &p);
		}
		else if (((ft_isdigit(e->line[p.i]) && is_aspace(e->line[p.i - 1])
					&& (e->line[p.i + 1] == '<' || e->line[p.i + 1] == '>'))
				   || (e->line[p.i] == '<' || e->line[p.i] == '>'))
				 && !p.quo && !p.escape)
		{
			if (p.ib > 0)
				parse_add_arg(e, &p);
			p.redirec_fd = -1;
			if (ft_isdigit(e->line[p.i]))
				p.redirec_fd = e->line[p.i++] - 48;
			parse_get_redirec_type(e, &p);
		}
		else if (is_aspace(e->line[p.i]) && !p.quo && !p.escape)
		{
			if (p.ib > 0)
				parse_add_arg(e, &p);
		}
		else if (e->line[p.i] == '\\' && !p.escape
				 && ((!p.quo) 
					 || (p.quo == DOUB && e->line[p.i + 1] == '"')
					 || (e->line[p.i + 1] == '\\')))
		{
			p.escape = 2;
		}
		else
		{
			p.buf[p.ib++] = e->line[p.i];
//			ft_printf("'%c' = '%s' = %d\n", p.buf[p.ib - 1], p.buf, p.buf[p.ib - 1]);
		}

		if (p.escape)
			p.escape--;

//		ft_printf("END i=%ld c='%c'\n", p.i, e->line[p.i]);
	}

	set_env_var(e, "_", p.last_arg);
	if (!p.error && p.a_id == 0)
	{
		if (!p.separ)
		{
			free_cmd_redirec(e, e->cid);
			e->nb_cmd--;
		}
		else
		p.error = EP_NULL_CMD;
	}
	if (!p.error && p.redirec)
		p.error = EP_MISS_REDIREC;


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
		else if (p.error == EP_BAD_FD)
			ft_putendl_fd("Bad file descriptor.", 2);
		else if (p.error == EP_SYNTAX)
			ft_putendl_fd("Syntax error.", 2);
	}

	free(p.buf);
	e->cid = 0;
//	ft_printf("'%s' %ld\n", e->cmd[0].arg[0], e->cmd[0].quo[0]);
//	ft_printf("nb_cmd=%ld\n", e->nb_cmd);

	if (!p.error)
		process_cmd(e);
	free_cmd(e);
}

void	parse_add_cmd(t_env *e, t_parse *p, char sep)
{
	int		old_size;
	int		new_size;

//	ft_printf("NEW CMD  arg_id=%ld\n", p->a_id);

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

//	ft_printf("ICI\n");
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

//	ft_printf("NEW ARG  '%s'\n", p->buf);

	old_size = sizeof(char*) * (p->a_id + 1);
	new_size = sizeof(char*) * (p->a_id + 2);
	parg = &e->cmd[e->cid].arg;
	if (p->a_id == 0)
		*parg = (char**)ft_memalloc(new_size);
	else
		*parg = (char**)ft_memrealloc(*parg, old_size, new_size);

//	ft_printf("->'%s' %ld '%ld'\n", p->buf, ft_strlen(p->buf), p->buf[ft_strlen(p->buf)]);
	e->cmd[e->cid].arg[p->a_id] = ft_strdup(p->buf);
	p->last_arg = e->cmd[e->cid].arg[p->a_id];
	e->cmd[e->cid].arg[p->a_id + 1] = NULL;
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

	if (p->redirec_fd < 0)
	{
		p->redirec_fd = 0;
		if (p->redirec == R_OUTA || p->redirec == R_OUT)
			p->redirec_fd = 1;
	}
	if (p->buf[0] == '&' )
	{
		if (!ft_isdigit(p->buf[1]) && p->buf[1] != '-')
			p->error = EP_BAD_FD;
		else if (p->buf[2])
			p->error = EP_SYNTAX;
		if (p->redirec == R_OUT)
			new_redirec(e, p->buf + 1, R_FDOUT, p->redirec_fd);
		else
			new_redirec(e, p->buf + 1, R_FDIN, p->redirec_fd);
	}
	else
		new_redirec(e, p->buf, p->redirec, p->redirec_fd);
	ft_strclr(p->buf);
	p->ib = 0;
	p->quo = NONE;
	p->redirec = NONE;
	p->redirec_fd = -1;
	return (0);
}

void	new_redirec(t_env *e, char *file, int type, int fd)
{
	t_redir		*new;
	t_redir		*tmp;

	new = (t_redir*)ft_memalloc(sizeof(t_redir));
	new->file = ft_strdup(file);
	new->type = type;
	new->fd = fd;
	new->fd_to = -1;
	if (file == NULL)
	{
		new->next = e->cmd[e->cid].redir;
		e->cmd[e->cid].redir = new;
		return ;
	}
	tmp = e->cmd[e->cid].redir;
	while (tmp && tmp->next)
		tmp = tmp->next;
	if (tmp)
		tmp->next = new;
	else
		e->cmd[e->cid].redir = new;
	if (type == R_HDOC)
		get_heredoc(e, file);
}

void	parse_get_redirec_type(t_env *e, t_parse *p)
{
	if (p->redirec)
		p->error = EP_MISS_REDIREC;
	if (e->line[p->i] == '>' && e->line[p->i + 1] != '>')
		p->redirec = R_OUT;
	else if (e->line[p->i] == '>' && e->line[p->i + 1] == '>')
	{
		p->redirec = R_OUTA;
		p->i++;
		if (e->line[p->i + 1] == '&')
			p->error = EP_SYNTAX;
	}
	else if (e->line[p->i] == '<' && e->line[p->i + 1] != '<')
		p->redirec = R_IN;
	else if (e->line[p->i] == '<' && e->line[p->i + 1] == '<')
	{
		p->redirec = R_HDOC;
		p->i++;
		if (e->line[p->i + 1] == '&')
			p->error = EP_SYNTAX;
	}
	while (is_aspace(e->line[p->i + 1]))
		p->i++;
//	ft_printf("->'%s'\n", e->line + p->i);
}

int		is_aspace(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

void	parse_cmd_cleanline(t_env *e)
{
	int		start;
	int		len;
	char	*temp;

//	ft_printf("line = '%s'\n", e->line);
	start = 0;
	while (e->line[start] && is_aspace(e->line[start]))
		start++;
	len = ft_strlen(e->line) - 1;
	while (len > 0 && is_aspace(e->line[len]))
		len--;
	temp = ft_strsub(e->line, start, len - start + 1);
	free(e->line);
	e->line = temp;
//	ft_printf("line = '%s'\n", e->line);
}

