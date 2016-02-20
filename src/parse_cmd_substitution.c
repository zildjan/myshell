/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_substitution.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/19 00:45:14 by pbourrie          #+#    #+#             */
/*   Updated: 2016/02/20 00:44:45 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	parse_cmd_substitution(t_env *e, t_parse *p)
{
	int		start;
	char	*cmd;
	char	*out;

	out = NULL;
	start = p->i++;
	parse_cmd_substitution_parse(e, p);
	cmd = ft_strsub(e->line, start + 1, p->i - start - 1);
//	ft_printf("\n%d->%d '%s'\n", start, p->i, cmd);
//	ft_printf("line='%s'\n", e->line + p->i);

	int		fd[2];
	pipe(fd);

	int		child;

	child = fork();
	if (child > 0)
	{
		char	buf[100];
		int		ret;

		out = ft_strdup("");
		ft_bzero(buf, 100);
		close(fd[1]);

		while (1)
		{
			ret = read(fd[0], &buf, 100);
			out = ft_strdupcat(out, buf);
			ft_bzero(buf, 100);
			if (ret < 1)
				break ;
		}

		waitpid(child, &ret, WUNTRACED);
	}
	else if (child == 0)
	{
		close(fd[0]);
		dup2(fd[1], 1);
		close(fd[1]);

		e->sub = 1;
		free(e->line);
		e->line = ft_strdup(cmd);
		free(cmd);

		parse_cmd(e);
		exit(0);
	}

	if (close(fd[0]) == -1)
		ft_putstr_fd("close error\n", 2);

	free(cmd);

	char	*save;
	save = e->line;
	e->line = ft_strsub(save, 0, start);
	e->line = ft_strdupcat(e->line, out);
	e->line = ft_strdupcat(e->line, save + p->i + 1);

	p->i = start;
	free(save);
	free(out);

}

void	parse_cmd_substitution_parse(t_env *e, t_parse *p)
{
	while (e->line[p->i])
	{
		if (e->line[p->i] == '\\')
			p->escape = 2;
		else if (e->line[p->i] == '`' && !p->escape)
		{
			break ;
		}
		p->i++;
		if (p->escape)
			p->escape--;
	}	
}
