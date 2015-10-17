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

void	parse_cmd_seq(t_env *e)
{
	int		i;

	i = 0;
	while (e->cmd_seq[i] != NULL)
	{
		e->cmd = e->cmd_seq[i];
		parse_cmd(e);
		i++;
	}
	free_cmd(e);
}

void	parse_cmd(t_env *e)
{
//	process_builtin(e);
	if (!process_builtin(e))
		process_cmd(e);
}

int		process_builtin(t_env *e)
{
//	ft_printf("%s\n", e->cmd[0]);
	if (ft_strequ(e->cmd[0], "exit"))
		exit(0);
	else if (ft_strequ(e->cmd[0], "env"))
		ft_putchartab(e->val);
	else
		return (0);
	return (1);
}

void	process_cmd(t_env *e)
{
	char	*cmd_path;
	int		father;
	int		ret;

	cmd_path = get_cmd_path(e, e->cmd[0]);
	if (cmd_path != NULL)
	{
		father = fork();
		if (father > 0)
			wait(&ret);
		else if (father == 0)
		{
			if (execve(cmd_path, e->cmd, e->val) == -1)
			{
				perror("!!!!");
				exit(0);
			}
		}
		free(cmd_path);
	}
	else
		ft_printf("command not found: %s\n", e->cmd[0]);
}
