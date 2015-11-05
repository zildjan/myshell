/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/09 19:55:32 by pbourrie          #+#    #+#             */
/*   Updated: 2015/10/09 21:27:14 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	builtin_cd(t_env *e)
{
	char	*new_pwd;

	if (!e->cmd[1])
		new_pwd = ft_strdup(e->home);
	else if (ft_strequ(e->cmd[1], "-"))
		new_pwd = get_env_val(e, "OLDPWD");
	else
	{
		if (e->cmd[1][0] == '~')
			new_pwd = parse_home_tilde(e, e->cmd[1]);
		else
			new_pwd = ft_strdup(e->cmd[1]);
	}
	if (chdir(new_pwd) == -1)
	{
		perror("!!! > ");
		put_error(0, new_pwd);
	}
	else
	{
		set_env_var(e, "OLDPWD", e->pwd);
		free(e->pwd);
		e->pwd = getcwd(NULL, 0);
		set_env_var(e, "PWD", e->pwd);
	}
	free(new_pwd);
}
