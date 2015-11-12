/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/10 18:58:17 by pbourrie          #+#    #+#             */
/*   Updated: 2015/11/12 22:39:52 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		process_builtin(t_env *e)
{
	if (ft_strequ(e->cmd[0], "cd"))
		builtin_cd(e);
	else if (ft_strequ(e->cmd[0], "exit"))
		builtin_exit(e);
	else if (ft_strequ(e->cmd[0], "setenv"))
		builtin_setenv(e);
	else if (ft_strequ(e->cmd[0], "unsetenv"))
		builtin_unsetenv(e);
	else if (ft_strequ(e->cmd[0], "env"))
		builtin_env(e);
	else
		return (0);
	return (1);
}

void	process_cmd(t_env *e, char **env)
{
	char	*cmd_path;

	cmd_path = get_cmd_path(e, e->cmd[0]);
	if (ft_strchr(e->cmd[0], '/') && ft_get_file_type(e->cmd[0]) == '-')
		cmd_path = ft_strdup(e->cmd[0]);
	if (cmd_path != NULL)
	{
		process_fork(e, cmd_path, env);
		free(cmd_path);
	}
	else
	{
		if (ft_strchr(e->cmd[0], '/'))
			put_error(ERRNOENT, NULL, e->cmd[0]);
		else
			put_error(ERRNOCMD, NULL, e->cmd[0]);
	}
}

void	process_fork(t_env *e, char *cmd_path, char **env)
{
	int		child;
	int		ret;

	ret = 0;
	child = fork();
	if (child > 0)
		wait(&ret);
	else if (child == 0)
	{
		if (execve(cmd_path, e->cmd, env) == -1)
		{perror("!!!");
			if (ft_get_file_mode(cmd_path) % 2 == 0)
				put_error(ERRACCES, NULL, e->cmd[0]);
			else
				put_error(ERREXEFORM, NULL, e->cmd[0]);
			exit(0);
		}
	}
	if (!WIFEXITED(ret))
	{
		put_sig_error(ret, e->cmd[0]);
		e->status = (WTERMSIG(ret)) + 128;
	}
	else
		e->status = WEXITSTATUS(ret);
}