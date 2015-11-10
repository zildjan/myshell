/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/09 19:26:19 by pbourrie          #+#    #+#             */
/*   Updated: 2015/11/10 20:17:25 by pbourrie         ###   ########.fr       */
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
		new_pwd = ft_strdup(e->cmd[1]);
	if (chdir(new_pwd) == -1)
		builtin_cd_error(new_pwd);
	else
	{
		set_env_var(e, "OLDPWD", e->pwd);
		free(e->pwd);
		e->pwd = getcwd(NULL, 0);
		set_env_var(e, "PWD", e->pwd);
	}
	free(new_pwd);
}

void	builtin_cd_error(char *path)
{
	char	type;
	int		mode;

	type = ft_get_file_type(path);
	mode = ft_get_file_mode(path);
	if (type == -1)
		put_error(ERRNOENT, ft_strdup("cd"), path);
	else if (type == '-')
		put_error(ERRNOTDIR, ft_strdup("cd"), path);
	else if ((mode / 100) % 2 == 0)
		put_error(ERRACCES, ft_strdup("cd"), path);
	else
		put_error(0, ft_strdup("cd"), path);
}
