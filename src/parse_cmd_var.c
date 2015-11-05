/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/09 19:55:32 by pbourrie          #+#    #+#             */
/*   Updated: 2015/10/09 21:27:14 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	parse_env_var(t_env *e, char *cmd)
{
	char	*new;
	int		c1;
	int		c2;

	new = ft_strnew(1000);
	c1 = 0;
	c2 = 0;
	while (cmd[c1])
	{
		if ((cmd[c1] == '$') && cmd[c1 + 1])
		{
			parse_var_replace(e, &cmd[c1], &new[c2], &c1, &c2);
		}
		else
			new[c2] = cmd[c1];
		c1++;
		c2++;
	}
		split_cmd_args(e, new);
	free(new);
}

void	parse_var_replace(t_env *e, char *cmd, char *new, int *c1, int *c2)
{
	int		i;
	char	*name;
	char	*val;
	int		limiter;

	ft_printf("precmd='%s'\n", cmd);
	limiter = 0;
	cmd++;
	i = 0;
	if (*cmd == '{')
	{
		limiter = 1;
		cmd = ft_strautosub(cmd, '{', '}');
		*c1 += 2;
	}
	else if (ft_strchr(cmd, '}'))
	{
		limiter = 1;
		cmd = ft_strautosub(cmd, -1, '}');
	}
	else if (ft_strchr(cmd, '$'))
	{
		limiter = 1;
		cmd = ft_strautosub(cmd, -1, '$');
	}
	if (ft_strchr(cmd, '$'))
		ft_putendl_fd("bad substitution", 2);
	ft_printf("cmd='%s'\n", cmd);
	*c1 += ft_strlen(cmd);
	while (e->var[i])
	{
		name = get_env_name(e, i);
		if (ft_strequ(name, cmd))
		{
			val = get_env_val(e, name);
			ft_strcat(new, val);
			*c2 += ft_strlen(val) - 1;
			free(val);
			free(name);
			break ;
		}
		free(name);
		i++;
	}
	if (ft_strequ("?", cmd))
	{
		val = ft_itoa(e->last_exit);
		ft_strcat(new, val);
		*c2 = ft_strlen(val);
		free(val);
	}
	if (limiter)
		free(cmd);
}

