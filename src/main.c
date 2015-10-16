/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/09 12:18:49 by pbourrie          #+#    #+#             */
/*   Updated: 2015/10/09 21:08:54 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include <errno.h>

void sighandler(int);

int		main(void)
{
	char *cmd;
	char **cmd_tab;
	int	father;
	int	ret;
	int i;
	t_env	*e;

	char	*cmd_path;
	cmd_path = NULL;

	signal(SIGINT, sighandler);

	e = init_env();

	while (1)
	{
		print_prompt();
		ret = get_next_line(0, &cmd);
		if (ret == 0)
		{
			ft_printf("exit\n");
			exit(0);
		}

		if (cmd == NULL)
		{

		}
		else if (ft_strequ(cmd, "exit"))
			exit(0);
		else if (ft_strequ(cmd, "env"))
			ft_putchartab(e->val);
		else
		{

			cmd_tab = ft_strsplit(cmd, ' ');
			if (cmd_tab[0] != NULL)
			{
				cmd_path = get_cmd_path(e, cmd_tab[0]);
				if (cmd_path != NULL)
				{
					father = fork();
					if (father > 0)
						wait(&ret);
					else if (father == 0)
					{
						if (execve(cmd_path, cmd_tab, e->val) == -1)
						{
							perror("!!!!");
							exit(0);
						}
					}
					free(cmd_path);
				}
				else
					ft_printf("command not found: %s\n", cmd_tab[0]);
			}
			i = 0;
			while (cmd_tab[i] != NULL)
			{
				free(cmd_tab[i]);
				i++;
			}
			if (cmd_tab != NULL)
				free(cmd_tab);
		}
		if (cmd)
			free(cmd);
		cmd = NULL;
	}

	return (0);
}


void sighandler(int signum)
{
//	ft_printf("Caught signal %d, coming out...\n", signum);
	if (signum != 239)
	ft_printf("\n                                      \r{bold}$> {rt}");
//	exit(1);
}
