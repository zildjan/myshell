/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/09 19:55:32 by pbourrie          #+#    #+#             */
/*   Updated: 2015/11/12 18:23:20 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	parse_var_expansion(t_env *e, t_parse *p)
{
	int		i;
	char	*arg;
	char	*new;
	char	*name;

	i = 0;
	while (ft_isalnum(e->line[++p->i]) || e->line[p->i] == '_'
		   || e->line[p->i] == '?')
		i++;
	arg = ft_strsub(&e->line[p->i - i], 0, i);
	p->i--;
	new = NULL;
	if (ft_strequ("?", arg))
		new = ft_itoa(e->status);
	i = 0;
	while (e->var[i])
	{
		name = get_env_name(e, i);
		if (ft_strequ(name, arg))
		{
			new = get_env_val(e, name);
			free(name);
			break ;
		}
		free(name);
		i++;
	}
	free(arg);
	if (new)
	{
		i = ft_strlen(new);
		p->ib += i;
		p->line_len += i;
		free(p->buf);
		p->buf = ft_strnew(p->line_len);		
		ft_strcat(p->buf, new);
		free(new);
	}
}

void	parse_tilde_expansion(t_env *e, t_parse *p)
{
	char	new[MAXPATHLEN + 1];

	ft_bzero(new, MAXPATHLEN + 1);
	if (e->line[p->i + 1] == '/' || is_aspace(e->line[p->i + 1])
		|| !e->line[p->i + 1])
		ft_strcpy(new, e->home);
	else
	{
		p->buf[p->ib++] = '~';
		return ;
	}
	p->line_len += ft_strlen(new);
	p->ib += ft_strlen(new);
	free(p->buf);
	p->buf = ft_strnew(p->line_len);
	ft_strcat(p->buf, new);
}
