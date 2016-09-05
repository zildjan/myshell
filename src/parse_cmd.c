/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/09 19:55:32 by pbourrie          #+#    #+#             */
/*   Updated: 2016/09/05 01:41:27 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	parse_cmd(t_env *e)
{
	t_parse	p;

//	ft_printf("PARSING\n");
	p.line_len = ft_strlen(e->line);
	if (p.line_len > MAX_LEN_LINE)
	{
		ft_putendl_fd("input line too long", 2);
		return ;
	}
	if (!p.line_len)
		return ;
	parse_init(e, &p);
	while (1)
	{
//		printf("[] b='%s' ib=%d\n", p.buf, p.ib);
		if (parse_cmd_check_eol(e, &p))
			break ;
		parse_cmd_quotes(e, &p);

		if (p.escape)
			p.escape--;
	}

//	ft_printf("END a_id=%d buf='%s' ib=%d l='%s' ", p.a_id, p.buf, p.ib, e->line+p.i);
//	ft_printf("line='%s'\n", e->line);

	parse_cmd_loop_end(e, &p);
	parse_cmd_put_error(&p);

	if (!p.error && e->cmd[e->cid].arg)//PAS SUR
		process_cmd(e);

	if (p.last_arg)
		free(p.last_arg);

//	ft_printf("ICI pid=%d\n", getpid());
	free_cmd(e);
}

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
	p->last_arg = NULL;
	p->redirec = NONE;
	p->error = 0;
	p->buf_len = p->line_len;
	p->buf = ft_strnew(p->buf_len);
	p->i = -1;
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
}

int		parse_cmd_check_eol(t_env *e, t_parse *p)
{
	if (p->error)
		return (1);
	if (!e->line[++p->i])
	{
		if (p->ib && !p->quo && !p->escape)
		{
			parse_add_arg(e, p);
			if (e->line[p->i])
				return (0);
		}

		if (parse_cmd_is_end(p))
		{
			p->error = EP_EOF;
		}
		return (1);
	}
	return (0);
}

void	parse_cmd_loop_end(t_env *e, t_parse *p)
{
	if (p->last_arg)
	{
		set_env_var(e, "_", p->last_arg);
		free(p->last_arg);
		p->last_arg = NULL;
	}
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
}

int		parse_cmd_is_end(t_parse *p)
{
	if (p->quo == SIMP)
		return ('\'');
	else if (p->quo == DOUB)
		return ('"');
	else if (p->bquo)
		return ('`');
	else if (p->escape)
		return ('\\');
	else if (p->sub > 0)
		return ('(');
	else if (!p->a_id && p->separ)
		return (p->separ);
	else
		return (0);
}
