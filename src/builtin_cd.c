/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/09 19:26:19 by pbourrie          #+#    #+#             */
/*   Updated: 2016/01/28 02:09:53 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	builtin_cd(t_env *e)
{
	char	opt_p;
	int		i;
	char	*new_pwd;
	char	*tmp;

	if ((i = builtin_cd_get_opt(e, &opt_p)) == -1)
		return ;
	if (!e->carg[i])
		new_pwd = ft_strdup(e->home);
	else if (e->carg[i][0] == '-' && !e->carg[i][1])
		new_pwd = get_env_val(e, "OLDPWD");
	else
		new_pwd = ft_strdup(e->carg[i]);
	if (!new_pwd)
		new_pwd = ft_strdup("");
	if (new_pwd[0] != '/')
	{
		tmp = ft_strjoin(e->pwd, "/");
		tmp = ft_strdupcat(tmp, new_pwd);
		free(new_pwd);
		new_pwd = tmp;
	}
	new_pwd = ft_strdupcat(new_pwd, "/");
	builtin_cd_clean_path(new_pwd, 0);
	builtin_cd_setenv(e, opt_p, new_pwd);
}

void	builtin_cd_setenv(t_env *e, char opt_p, char *new_pwd)
{
	char	*tmp;

	if (chdir(new_pwd) == -1)
	{
		builtin_cd_error(e, new_pwd, 0);
		free(new_pwd);
		return ;
	}
	if (opt_p)
	{
		free(new_pwd);
		new_pwd = getcwd(NULL, 0);
	}
	e->status = 0;
//	ft_putchartab(e->var);
	set_env_var(e, "OLDPWD", e->pwd);
	tmp = new_pwd;
	ft_printf("!!!\n");
	free(e->pwd);
	e->pwd = tmp;
	set_env_var(e, "PWD", e->pwd);
}

int		builtin_cd_get_opt(t_env *e, char *opt_p)
{
	int		i;
	int		i2;

	*opt_p = 0;
	i = 0;
	while (e->carg[++i])
	{
		i2 = 0;
		if (e->carg[i][i2] == '-')
			while (e->carg[i][++i2] && i2 > 0)
			{
				if (e->carg[i][i2] == 'P')
					*opt_p = 1;
				else if (e->carg[i][i2] == 'L')
					*opt_p = 0;
				else
				{
					builtin_cd_error(e, NULL, e->carg[i][i2]);
					return (-1);
				}
			}
		if (i2 <= 1)
			break ;
	}
	return (i);
}

void	builtin_cd_error(t_env *e, char *path, char opt)
{
	char	type;
	int		mode;
	char	*file;

	e->status = 1;
	if (opt)
	{
		put_cmd_opt_error("cd", opt, e->cmd[e->cid].fd_err, "[-L|-P] [dir]");
		return ;
	}
	type = ft_get_file_type(path);
	mode = ft_get_file_mode(path);
	file = ft_get_dir_up(path, 0);
	if (type == -1)
		put_error(ERRNOENT, ft_strdup("cd"), file, e->cmd[e->cid].fd_err);
	else if (type == '-')
		put_error(ERRNOTDIR, ft_strdup("cd"), file, e->cmd[e->cid].fd_err);
	else if ((mode / 100) % 2 == 0)
		put_error(ERRACCES, ft_strdup("cd"), file, e->cmd[e->cid].fd_err);
	else
		put_error(0, ft_strdup("cd"), file, e->cmd[e->cid].fd_err);
	if (file)
		free(file);
}
