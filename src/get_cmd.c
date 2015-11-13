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

	ret = get_next_line(0, &e->usr_cmd);
	if (ret == 0)
	{
		ft_printf("exit\n");
		builtin_exit(e);
	}
	if (e->usr_cmd == NULL)
		return ;
	parse_cmd_seq(e);
	free(e->usr_cmd);
	e->usr_cmd = NULL;
}

void	parse_cmd_seq(t_env *e)
{
	char	**cmd_seq;
	int		i;

	cmd_seq = ft_strsplit(e->usr_cmd, ';');
	if (cmd_seq == NULL)
		return ;
	i = 0;
	while (cmd_seq[i] != NULL)
	{
		split_cmd_args(e, cmd_seq[i]);
		free(cmd_seq[i]);
		i++;
	}
	free(cmd_seq);
}

void	split_cmd_args(t_env *e, char *cmd)
{
	e->cmd = ft_strsplit(cmd, ' ');
	if (e->cmd == NULL)
		return ;
	parse_cmd(e);
	free_cmd(e);
}
