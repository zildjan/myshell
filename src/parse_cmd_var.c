/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/09 19:55:32 by pbourrie          #+#    #+#             */
/*   Updated: 2015/11/09 21:47:06 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	parse_env_var(t_env *e, int i)
{
	char	*arg;

	arg = e->cmd[i];
	if (arg[0] == '$' && arg[1])
	{
		arg++;
		parse_env_var_replace(e, arg, &e->cmd[i]);
	}
}

void	parse_env_var_replace(t_env *e, char *arg, char **cmd)
{
	int		i;
	char	*new;
	char	*name;

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
	if (new)
	{
		free(*cmd);
		*cmd = new;
	}
}

