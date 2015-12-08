/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_setenv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/09 19:55:32 by pbourrie          #+#    #+#             */
/*   Updated: 2015/11/12 19:36:00 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	builtin_setenv(t_env *e)
{
	if (!e->carg[1])
		ft_putchartab(e->var);
	else if (e->carg[2] && e->carg[3])
		ft_putendl_fd("setenv: Too many arguments.", 2);
	else if (!ft_strcheck(e->carg[1], ft_isascii))
		ft_putendl_fd("setenv: Non ascii character.", 2);
	else if (e->carg[2] && !ft_strcheck(e->carg[2], ft_isascii))
		ft_putendl_fd("setenv: Non ascii character.", 2);
	else if (e->carg[1] && ft_strchr(e->carg[1], '='))
		ft_putendl_fd("setenv: Syntax error : '='.", 2);
	else if (e->carg[2] && ft_strchr(e->carg[2], '='))
		ft_putendl_fd("setenv: Syntax error : '='.", 2);
	else
		set_env_var(e, e->carg[1], e->carg[2]);
}

void	builtin_unsetenv(t_env *e)
{
	int		i;

	if (!e->carg[1])
		ft_putendl_fd("unsetenv: Too few arguments.", 2);
	else
	{
		i = 0;
		while (e->carg[i])
		{
			unset_env_var(e, e->carg[i]);
			i++;
		}
	}
}
