/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/09 19:26:19 by pbourrie          #+#    #+#             */
/*   Updated: 2016/01/21 01:55:19 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	builtin_cd(t_env *e)
{
	char	opt_p;
	int		i;
	char	*new_pwd;

	if ((i = builtin_cd_get_opt(e, &opt_p)) == -1)
		return ;
//	ft_printf("opt_P=%d i=%d arg=%s '%p'\n", opt_p, i, e->carg[i], e->carg[i]);

	if (!e->carg[i])
		new_pwd = ft_strdup(e->home);
	else if (e->carg[i][0] == '-' && !e->carg[i][1])
		new_pwd = get_env_val(e, "OLDPWD");
	else
		new_pwd = ft_strdup(e->carg[i]);

	char	*tmp;

	if (new_pwd[0] != '/')
	{
		tmp = ft_strjoin(e->pwd, "/");
		tmp = ft_strdupcat(tmp, new_pwd);
		free(new_pwd);
		new_pwd = tmp;
	}

	ft_printf("'%s'\n", new_pwd);
	builtin_cd_clean_path(new_pwd);
	ft_printf("'%s'\n", new_pwd);

	if (chdir(new_pwd) == -1)
	{
		builtin_cd_error(e, new_pwd, 0);
		return ;
	}

	if (opt_p)
	{
		free(new_pwd);
		new_pwd = getcwd(NULL, 0);
	}


	builtin_cd_setenv(e, new_pwd);
//	free(new_pwd);
}

void	builtin_cd_setenv(t_env *e, char *new_pwd)
{
	char	*tmp;

	e->status = 0;
	set_env_var(e, "OLDPWD", e->pwd);
	tmp = new_pwd;
	free(e->pwd);
	e->pwd = tmp;
	set_env_var(e, "PWD", e->pwd);
}

void	builtin_cd_clean_path(char *new_pwd)
{
	int		i;

	i = -1;
	while (new_pwd[++i])
		while (new_pwd[i] == '.' && new_pwd[i + 1] != '/')
			ft_strcpy(new_pwd + i, new_pwd + i + 1);
	i = -1;
	while (new_pwd[++i])
		while (new_pwd[i] == '/' && new_pwd[i + 1] == '/')
			ft_strcpy(new_pwd + i, new_pwd + i + 1);



//	if (new_pwd[i - 1] == '/')
//		new_pwd[i - 1] = 0;

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
		if (i2 == 0)
			break ;
	}
	return (i);
}

void	builtin_cd_error(t_env *e, char *path, char opt)
{
	char	type;
	int		mode;

	e->status = 1;
	if (opt)
	{
		put_cmd_opt_error("cd", opt, e->cmd[e->cid].fd_err, "[-L|-P] [dir]");
		return ;
	}
	type = ft_get_file_type(path);
	mode = ft_get_file_mode(path);
	if (type == -1)
		put_error(ERRNOENT, ft_strdup("cd"), path, e->cmd[e->cid].fd_err);
	else if (type == '-')
		put_error(ERRNOTDIR, ft_strdup("cd"), path, e->cmd[e->cid].fd_err);
	else if ((mode / 100) % 2 == 0)
		put_error(ERRACCES, ft_strdup("cd"), path, e->cmd[e->cid].fd_err);
	else
		put_error(0, ft_strdup("cd"), path, e->cmd[e->cid].fd_err);
}
