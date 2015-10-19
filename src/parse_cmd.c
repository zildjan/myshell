/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/09 19:55:32 by pbourrie          #+#    #+#             */
/*   Updated: 2015/10/09 21:27:14 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	parse_cmd(t_env *e)
{
	if (e->cmd[0] == NULL)
		return ;
	if (!process_builtin(e))
		process_cmd(e);
}

int		process_builtin(t_env *e)
{
//	ft_printf("%s\n", e->cmd[0]);
	if (ft_strequ(e->cmd[0], "cd"))
		builtin_cd(e);
	else if (ft_strequ(e->cmd[0], "exit"))
		exit(0);
	else if (ft_strequ(e->cmd[0], "setenv"))
		builtin_setenv(e);
	else if (ft_strequ(e->cmd[0], "unsetenv"))
		builtin_unsetenv(e);
	else if (ft_strequ(e->cmd[0], "env"))
		ft_putchartab(e->var);
	else
		return (0);
	return (1);
}

void	process_cmd(t_env *e)
{
	char	*cmd_path;

	cmd_path = get_cmd_path(e, e->cmd[0]);
	if (ft_strchr(e->cmd[0], '/') && ft_get_file_type(e->cmd[0]) == '-')
		cmd_path = ft_strdup(e->cmd[0]);
	if (cmd_path != NULL)
	{
		process_fork(e, cmd_path);
		free(cmd_path);
	}
	else
	{
		if (ft_strchr(e->cmd[0], '/'))
			put_error(ERRNOENT, e->cmd[0]);
		else
			put_error(ERRNOCMD, e->cmd[0]);
	}
}

void	process_fork(t_env *e, char *cmd_path)
{
	int		father;
	int		ret;

	father = fork();
	if (father > 0)
		wait(&ret);
	else if (father == 0)
	{
		if (execve(cmd_path, e->cmd, e->var) == -1)
		{
			if (ft_get_file_mode(cmd_path) % 2 == 0)
				put_error(ERRACCES, e->cmd[0]);
			else
				put_error(ERREXEFORM, e->cmd[0]);
				exit(0);
		}
	}
}
