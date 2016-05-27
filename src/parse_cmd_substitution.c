/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_substitution.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/19 00:45:14 by pbourrie          #+#    #+#             */
/*   Updated: 2016/05/28 01:30:50 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	parse_cmd_substitution(t_env *e, t_parse *p)
{
	int		start;
	char	*cmd;
	char	*out;

	out = NULL;
	cmd = ft_strnew(p->line_len);
	start = p->i++;
	if (!parse_cmd_substitution_gotoend(e, p, cmd))
	{
		p->error = EP_EOF;
		free(cmd);
		return ;
	}
//	cmd = ft_strsub(e->line, start + 1, p->i - start - 1);

//	ft_printf("cmd='%s'\n", cmd);

	int		fd[2];
	pipe(fd);

	int		child;

	child = fork();
	if (child == 0)
	{
		close(fd[0]);
		dup2(fd[1], 1);
		close(fd[1]);
		free(e->line);
		e->line = ft_strdup(cmd);
		free(cmd);
		parse_cmd(e);
		exit(e->status);
	}

	char	buf[100];
	int		ret;

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

	waitpid(child, &ret, WUNTRACED);
	e->status = WEXITSTATUS(ret);

 	if (close(fd[0]) == -1)
		ft_putstr_fd("close error\n", 2);

	free(cmd);

	int		i;

	i = ft_strlen(out) - 1;
	while (out[i] == '\n')
		out[i--] = 0;

	char	*save;
	save = e->line;
	e->line = ft_strsub(save, 0, start);
	e->line = ft_strdupcat(e->line, out);
	e->line = ft_strdupcat(e->line, save + p->i + 1);

	p->ignore = start + ft_strlen(out);

//	ft_printf("ignore=%d -> '%s'\nline='%s'\n", p->ignore, e->line + p->ignore, e->line);

	p->line_len = ft_strlen(e->line);

	p->i = start - 1;
	free(save);
	free(out);

}

int		parse_cmd_substitution_gotoend(t_env *e, t_parse *p, char *cmd)
{
	int		i;

	i = 0;
	while (e->line[p->i])
	{
		if (e->line[p->i] == '\\')
			p->escape = 2;
		else if (e->line[p->i] == '`' && !p->escape)
			return (1);
		else
			cmd[i++] = e->line[p->i];
		p->i++;
		if (p->escape)
			p->escape--;
	}
	return (0);
}
