/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_substitution.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/19 00:45:14 by pbourrie          #+#    #+#             */
/*   Updated: 2016/09/10 02:26:33 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	parse_cmd_substitution(t_env *e, t_parse *p)
{
	int		start;
	char	*cmd;
	int		fd[2];
	char	*out;
	char	save[2];

	cmd = ft_strnew(p->line_len);
	start = p->i++;
	save[0] = p->escape;
	save[1] = p->quo;
	if (!parse_cmd_substi_parse_line(e, p, cmd))
	{
		p->error = EP_EOF;
		free(cmd);
		return ;
	}
	p->escape = save[0];
	p->quo = save[1];
	pipe(fd);
	out = parse_cmd_substitution_fork(e, fd, cmd);
	parse_cmd_substi_line(e, p, out, start);
}

char	*parse_cmd_substitution_fork(t_env *e, int *fd, char *cmd)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		e->sub = 1;
		signal_default();
		close(fd[0]);
		dup2(fd[1], 1);
		close(fd[1]);
		free(e->line);
		e->line = ft_strdup(cmd);
		free(cmd);
		parse_cmd(e);
		exit(e->status);
	}
	free(cmd);
	return (parse_cmd_substitution_get_output(e, fd, pid));
}

char	*parse_cmd_substitution_get_output(t_env *e, int *fd, pid_t pid)
{
	char	buf[100];
	int		ret;
	char	*out;

	out = NULL;
	out = ft_strdup("");
	ft_bzero(buf, 100);
	close(fd[1]);
	while (1)
	{
		ret = read(fd[0], &buf, 99);
		out = ft_strdupcat(out, buf);
		ft_bzero(buf, 100);
		if (ret < 1)
			break ;
	}
	waitpid(pid, &ret, WUNTRACED);
	e->status = WEXITSTATUS(ret);
	if (close(fd[0]) == -1)
		ft_putstr_fd("close error\n", 2);
	return (out);
}

void	parse_cmd_substi_line(t_env *e, t_parse *p, char *out, int start)
{
	int		i;
	char	*save;

	i = ft_strlen(out) - 1;
	while (out[i] == '\n')
		out[i--] = 0;
	save = e->line;
	e->line = ft_strsub(save, 0, start);
	e->line = ft_strdupcat(e->line, out);
	e->line = ft_strdupcat(e->line, save + p->i + 1);
	p->ignore = start + ft_strlen(out);
	p->line_len = ft_strlen(e->line);
	p->quoted = 1;
	p->i = start - 1;
	free(save);
	free(out);
}
