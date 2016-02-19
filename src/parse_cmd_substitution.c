/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_substitution.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/19 00:45:14 by pbourrie          #+#    #+#             */
/*   Updated: 2016/02/19 02:11:45 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	parse_cmd_substitution(t_env *e, t_parse *p)
{
	int		start;
	char	*cmd;

	start = p->i++;
	parse_cmd_substitution_parse(e, p);
	cmd = ft_strsub(e->line, start + 1, p->i - start - 1);
//	ft_printf("\n%d->%d '%s'\n", start, p->i, cmd);
//	ft_printf("line='%s'\n", e->line + p->i);

	int		child;

	child = fork();
	if (child > 0)
	{
		int		ret;
		waitpid(child, &ret, WUNTRACED);
	}
	else if (child == 0)
	{
//		e->sub = 1;
		free(e->line);
		e->line = ft_strdup(cmd);
		free(cmd);

		parse_cmd(e);
//		free_env(e);

//		while (1)
//			sleep(2);
		exit(0);
	}

	free(cmd);
	p->i++;
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
