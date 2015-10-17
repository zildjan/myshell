/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/09 19:55:32 by pbourrie          #+#    #+#             */
/*   Updated: 2015/10/09 21:27:14 by pbourrie         ###   ########.fr       */
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
		exit(0);
	}
	if (e->usr_cmd)
		get_cmd_seq(e);
}

void	get_cmd_seq(t_env *e)
{
	char	**cmd_seq;
	int		i;
//	char	*temp;

//	ft_printf("'%s'\n", e->usr_cmd);

	cmd_seq = ft_strsplit(e->usr_cmd, ';');
	if (cmd_seq)
	{
		i = 0;
		while (cmd_seq[i] != NULL)
		{
//			temp = ft_strtrim(cmd_seq[i]);
//			free(cmd_seq[i]);
//			cmd_seq[i] = temp;
//			ft_printf("%ld->'%s'\n", i, cmd_seq[i]);

			i++;
		}
		e->cmd_seq = (char***)ft_memalloc(sizeof(char*) * (i + 1));
		get_cmd_opts(e, cmd_seq);
	}
}

void	get_cmd_opts(t_env *e, char **cmd_seq)
{
	int	i;

	i = 0;
	while (cmd_seq[i] != NULL)
	{
		e->cmd_seq[i] = ft_strsplit(cmd_seq[i], ' ');
		free(cmd_seq[i]);
		i++;
	}
	e->cmd_seq[i] = NULL;
	free(cmd_seq);
	parse_cmd_seq(e);
}
