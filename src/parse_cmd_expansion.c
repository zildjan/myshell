/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/09 19:55:32 by pbourrie          #+#    #+#             */
/*   Updated: 2016/07/09 01:58:06 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	parse_var_expansion(t_env *e, t_parse *p)
{
	int		i;
	char	*arg;
	char	*new;

	i = 1;
	while (ft_isalnum(e->line[i + p->i]) || e->line[i + p->i] == '_'
			|| e->line[i + p->i] == '?')
		i++;
	i--;
	arg = ft_strsub(&e->line[p->i + 1], 0, i);
//	ft_printf("='%s'\n", arg);
	new = NULL;
	if (ft_strequ("?", arg))
		new = ft_itoa(e->status);
	parse_var_expansion2(e, p, arg, new);
}

void	parse_var_expansion2(t_env *e, t_parse *p, char *arg, char *new)
{
	char	*name;
	int		i;

	i = -1;
	while (e->var[++i])
	{
		name = get_env_name(e, i);
		if (ft_strequ(name, arg))
		{
			new = get_env_val(e, name);
			free(name);
			break ;
		}
		free(name);
	}

	p->quoted = 1;

	name = ft_strsub(e->line, 0, p->i);
	if (new)
	{
		name = ft_strdupcat(name, new);
//		ft_printf("NAME='%s'\n", name);
		free(new);
	}
	name = ft_strdupcat(name, e->line + (p->i + ft_strlen(arg) + 1));
//	ft_printf("FIN='%s'\n", e->line + (p->i + ft_strlen(arg) + 1));

	free(e->line);
	e->line = name;
	p->line_len = ft_strlen(e->line);
	p->i--;
	free(arg);

//	ft_printf("NEW='%s'\n", e->line);
}

void	parse_tilde_expansion(t_env *e, t_parse *p)
{
	char	new[MAXPATHLEN + 1];
	int		len;

	ft_bzero(new, MAXPATHLEN + 1);
	if (e->line[p->i + 1] == '/' || is_aspace(e->line[p->i + 1])
		|| !e->line[p->i + 1])
		ft_strcpy(new, e->home);
	else
	{
		p->buf[p->ib++] = '~';
		return ;
	}
	p->quoted = 1;
	len = ft_strlen(new);
	p->line_len += len;
	p->ib += len;
	realloc_parse_buffer(p, len);
	ft_strcat(p->buf, new);
}
