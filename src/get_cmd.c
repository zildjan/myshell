/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/09 19:55:32 by pbourrie          #+#    #+#             */
/*   Updated: 2015/11/13 21:54:46 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	get_cmd(t_env *e)
{
	int		ret;

	ret = get_next_line(0, &e->line);
	if (ret == 0)
	{
		ft_printf("exit\n");
		builtin_exit(e);
	}
	if (e->line == NULL)
		return ;
	parse_cmd(e);
	free(e->line);
	e->line = NULL;
}




/*
void	parse_cmd_seq(t_env *e)
{
	char	**cmd_seq;
	int		i;

	cmd_seq = ft_strsplit(e->line, ';');
	if (cmd_seq == NULL)
		return ;
	i = 0;
	while (cmd_seq[i] != NULL)
	{
		if (!ft_isfullof(cmd_seq[i], ' '))
			split_cmd_pipes(e, cmd_seq[i]);
		free(cmd_seq[i]);
		i++;
	}
	free(cmd_seq);
}

void	split_cmd_pipes(t_env *e, char *cmd)
{
	char	**pipes;
	int		i;

	pipes = ft_strsplit(cmd, '|');
	if (pipes == NULL)
		return ;
	e->nb_cmd = 0;
	i = -1;
	while (pipes[++i])
	{
		if (!ft_isfullof(pipes[i], ' '))
			pipes[e->nb_cmd++] = pipes[i];
		else
			free(pipes[i]);
	}
	pipes[e->nb_cmd] = NULL;
	if (e->nb_cmd > 0)
		split_cmd_args(e, pipes);
	free(pipes);
}

void	split_cmd_args(t_env *e, char **pipes)
{
	int		i;

	e->cid = 0;
	e->cmd_pgid = 0;
	e->cmd = (t_cmd*)ft_memalloc(sizeof(t_cmd) * (e->nb_cmd));
	i = -1;
	while (pipes[++i])
	{
		e->cmd[i].arg = ft_strsplit(pipes[i], ' ');
		free(pipes[i]);
	}
	if (e->cmd[0].arg == NULL)
		return ;
//	parse_redirections(e);
	parse_cmd(e);
	free_cmd(e);
}
// */
