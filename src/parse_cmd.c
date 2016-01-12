/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/09 19:55:32 by pbourrie          #+#    #+#             */
/*   Updated: 2016/01/12 01:33:19 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	parse_cmd(t_env *e)
{
	t_parse	p;

	parse_cmd_cleanline(e);
	p.line_len = ft_strlen(e->line);
	if (p.line_len > MAX_LEN_LINE)
	{
		ft_putendl_fd("input line too long", 2);
		return ;
	}
	if (!p.line_len)
		return ;
	parse_cmd_init(e, &p);
	while (1)
	{
		if (parse_cmd_check_eol(e, &p))
			break ;
		parse_cmd_quotes(e, &p);
		if (p.escape)
			p.escape--;
	}
	parse_cmd_loop_end(e, &p);
	parse_cmd_put_error(&p);
	if (!p.error)
		process_cmd(e);
	free_cmd(e);
}

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

int		parse_add_redirec(t_env *e, t_parse *p)
{
	if (!p->ib)
		return (p->error = EP_MISS_REDIREC);
	if (p->redirec_fd < 0)
	{
		p->redirec_fd = 0;
		if (p->redirec == R_OUTA || p->redirec == R_OUT)
			p->redirec_fd = 1;
	}
	if (p->buf[0] == '&')
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
	parse_add_redirec_p2(p);
	return (0);
}

void	parse_add_redirec_p2(t_parse *p)
{
	ft_strclr(p->buf);
	p->ib = 0;
	p->quo = NONE;
	p->redirec = NONE;
	p->redirec_fd = -1;
}

void	new_redirec(t_env *e, char *file, int type, int fd)
{
	t_redir		*new;
	t_redir		*tmp;

	new = (t_redir*)ft_memalloc(sizeof(t_redir));
	new->file = dup_arg(file);
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

	start = 0;
	while (e->line[start] && is_aspace(e->line[start]))
		start++;
	len = ft_strlen(e->line) - 1;
	while (len > 0 && is_aspace(e->line[len]))
		len--;
	temp = ft_strsub(e->line, start, len - start + 1);
	free(e->line);
	e->line = temp;
}

void	realloc_parse_buffer(t_parse *p, int add)
{
	int		old;
	int		new;

	old = sizeof(char) * p->buf_len;
	new = sizeof(char) * (p->buf_len + add);
	p->buf = ft_memrealloc(p->buf, old, new);
	p->buf_len += add;
}

char	*dup_arg(char *buf)
{
	if (!buf)
		return (NULL);
	if (ft_strlen(buf) > MAX_LEN_ARG)
		return (ft_strndup(buf, MAX_LEN_ARG));
	return (ft_strdup(buf));
}

void	parse_cmd_init(t_env *e, t_parse *p)
{
	e->cid = 0;
	p->a_id = 0;
	e->nb_cmd = 1;
	p->quo = NONE;
	p->escape = 0;
	p->separ = 0;
	p->last_arg = NULL;
	p->redirec = NONE;
	p->error = 0;
	p->buf_len = p->line_len;
	p->buf = ft_strnew(p->buf_len);
	p->i = -1;
	p->ib = 0;
	e->cmd = (t_cmd*)ft_memalloc(sizeof(t_cmd) * (e->nb_cmd));
	e->cmd[0].redir = NULL;
	e->cmd[0].hdoc = NULL;
	e->cmd[0].condi = 0;
	e->cmd[0].fd_in = 0;
	e->cmd[0].fd_out = 1;
	e->cmd[0].fd_err = 2;
}

int		parse_cmd_check_eol(t_env *e, t_parse *p)
{
	if (p->error)
		return (1);
	if (!e->line[++p->i])
		if (parse_cmd_get_eol(e, p))
			return (1);
	return (0);
}

int		parse_cmd_get_eol(t_env *e, t_parse *p)
{
	if (e->term)
		history_add(e, p->escape);
	if (p->ib && !p->quo && !p->escape)
		parse_add_arg(e, p);
	if (p->quo == SIMP)
		p->error = get_cmd_end(e, '\'');
	else if (p->quo == DOUB)
		p->error = get_cmd_end(e, '"');
	else if (p->escape)
		p->error = get_cmd_end(e, 0);
	else if (!p->a_id && p->separ)
		p->error = get_cmd_end(e, p->separ);
	else
		return (1);
	if (p->quo && !p->escape)
		p->buf[p->ib++] = '\n';
	parse_cmd_cleanline(e);
	p->line_len = ft_strlen(e->line);
	if (p->line_len > MAX_LEN_LINE || (!p->line_len && p->escape))
		return (1);
	p->i = 0;
	p->escape = 0;
	return (0);
}

int		parse_cmd_quotes(t_env *e, t_parse *p)
{
	if (e->line[p->i] == '\'' && (!p->quo || p->quo == SIMP)
		&& !p->escape)
	{
		if (p->quo)
			p->quo = NONE;
		else
			p->quo = SIMP;
	}
	else if (e->line[p->i] == '"' && (!p->quo || p->quo == DOUB)
			&& !p->escape)
	{
		if (p->quo)
			p->quo = NONE;
		else
			p->quo = DOUB;
	}
	else
		return (parse_cmd_operator(e, p));
	return (1);
}

int		parse_cmd_operator(t_env *e, t_parse *p)
{
	if (e->line[p->i] == '&' && e->line[p->i + 1] == '&'
		&& !p->quo && !p->escape)
	{
		p->i++;
		if (p->ib > 0)
			parse_add_arg(e, p);
		if (p->a_id == 0)
			p->error = EP_NULL_CMD;
		else
			parse_add_cmd(e, p, SEP_AND);
	}
	else if (e->line[p->i] == '|' && e->line[p->i + 1] == '|'
			&& !p->quo && !p->escape)
	{
		p->i++;
		if (p->ib > 0)
			parse_add_arg(e, p);
		if (p->a_id == 0)
			p->error = EP_NULL_CMD;
		else
			parse_add_cmd(e, p, SEP_OR);
	}
	else
		return (parse_cmd_pipe_comma(e, p));
	return (1);
}

int		parse_cmd_pipe_comma(t_env *e, t_parse *p)
{
	if (e->line[p->i] == '|' && !p->quo
		&& !p->escape)
	{
		if (p->ib > 0)
			parse_add_arg(e, p);
		if (p->a_id == 0)
			p->error = EP_NULL_CMD;
		else
			parse_add_cmd(e, p, SEP_PIPE);
	}
	else if (e->line[p->i] == ';' && !p->quo
			&& !p->escape)
	{
		if (p->ib > 0)
			parse_add_arg(e, p);
		if (p->a_id == 0)
			p->error = EP_NULL_CMD;
		else
			parse_add_cmd(e, p, NONE);
	}
	else
		return (parse_cmd_expansion(e, p));
	return (1);
}

int		parse_cmd_expansion(t_env *e, t_parse *p)
{
	if (e->line[p->i] == '$' && p->quo != SIMP
		&& !p->escape)
	{
		parse_var_expansion(e, p);
	}
	else if (e->line[p->i] == '~' && !p->quo && !p->ib
			&& !p->escape)
	{
		parse_tilde_expansion(e, p);
	}
	else
		return (parse_cmd_redirection(e, p));
	return (1);
}

int		parse_cmd_redirection(t_env *e, t_parse *p)
{
	if (((ft_isdigit(e->line[p->i]) && is_aspace(e->line[p->i - 1])
		&& (e->line[p->i + 1] == '<' || e->line[p->i + 1] == '>'))
		|| (e->line[p->i] == '<' || e->line[p->i] == '>'))
		&& !p->quo && !p->escape)
	{
		if (p->ib > 0)
			parse_add_arg(e, p);
		p->redirec_fd = -1;
		if (ft_isdigit(e->line[p->i]))
			p->redirec_fd = e->line[p->i++] - 48;
		parse_get_redirec_type(e, p);
	}
	else
		return (parse_cmd_space_backslash(e, p));
	return (1);
}

int		parse_cmd_space_backslash(t_env *e, t_parse *p)
{
	if (is_aspace(e->line[p->i]) && !p->quo && !p->escape)
	{
		if (p->ib > 0)
			parse_add_arg(e, p);
	}
	else if (e->line[p->i] == '\\' && !p->escape
			&& ((!p->quo)
				|| (p->quo == DOUB && e->line[p->i + 1] == '"')
				|| (p->quo == DOUB && !e->line[p->i + 1])
				|| (e->line[p->i + 1] == '\\')))
	{
		p->escape = 2;
	}
	else
		return (parse_cmd_add_to_buf(e, p));
	return (1);
}

int		parse_cmd_add_to_buf(t_env *e, t_parse *p)
{
	if (p->ib + 10 >= p->buf_len)
		realloc_parse_buffer(p, 10);
	if (e->line[p->i])
		p->buf[p->ib++] = e->line[p->i];
	return (1);
}

void	parse_cmd_loop_end(t_env *e, t_parse *p)
{
	set_env_var(e, "_", p->last_arg);
	if (!p->error && p->a_id == 0)
	{
		if (!p->separ)
		{
			free_heredoc(e, e->cid);
			free_cmd_redirec(e, e->cid);
			e->nb_cmd--;
		}
		else
			p->error = EP_NULL_CMD;
	}
	if (!p->error && p->redirec)
		p->error = EP_MISS_REDIREC;
	free(p->buf);
	e->cid = 0;
	history_save_ent(e);
}

void	parse_cmd_put_error(t_parse *p)
{
	if (p->error)
	{
		if (p->error == EP_NULL_CMD)
			ft_putendl_fd("Invalid null command.", 2);
		else if (p->error == EP_AMB_OUT)
			ft_putendl_fd("Ambiguous output redirect.", 2);
		else if (p->error == EP_AMB_IN)
			ft_putendl_fd("Ambiguous input redirect.", 2);
		else if (p->error == EP_MISS_REDIREC)
			ft_putendl_fd("Missing name for redirect.", 2);
		else if (p->error == EP_BAD_FD)
			ft_putendl_fd("Bad file descriptor.", 2);
		else if (p->error == EP_SYNTAX)
			ft_putendl_fd("Syntax error.", 2);
		else if (p->error == EP_EOF)
			ft_putendl_fd("Syntax error: unexpected end of file", 2);
	}
}
