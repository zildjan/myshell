/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/09 19:55:32 by pbourrie          #+#    #+#             */
/*   Updated: 2016/01/28 02:14:23 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	set_new_env_var(t_env *e, char *name, char *val)
{
	int		i;
	char	*temp;

	i = 0;
	while (e->var[i] != NULL)
		i++;
	temp = ft_strjoin(name, "=");
	e->var[i] = ft_strjoin(temp, val);
	e->var[i + 1] = NULL;
	free(temp);
	resize_env_tab(e, 1);
}

void	set_env_var(t_env *e, char *name, char *val)
{
	int		i;
	char	*temp;

	i = get_env_id(e, name);
	if (i == -1)
		set_new_env_var(e, name, val);
	else
	{
		free(e->var[i]);
		temp = ft_strjoin(name, "=");
		e->var[i] = ft_strjoin(temp, val);
		free(temp);
	}
	refresh_sh_var(e, name);
}

int		unset_env_var(t_env *e, char *name)
{
	int		i;

	ft_printf("DEBUT UNSET\n");
	i = get_env_id(e, name);
	if (i == -1)
		return (0);
	free(e->var[i]);
	i++;
	while (e->var[i] != NULL)
	{
		e->var[i - 1] = e->var[i];
		i++;
	}
	e->var[i - 1] = NULL;
	refresh_sh_var(e, name);
	resize_env_tab(e, -1);
	ft_printf("FIN UNSET\n");
	return (1);
}

void	resize_env_tab(t_env *e, int new)
{
	int		old_size;
	int		new_size;
	int		i;

	ft_printf("ICI1  %d\n", e->tab_size);
	i = 0;
	while (e->var[i])
		i++;
	if ((e->tab_size + new) <= i)
		return ;
	old_size = sizeof(char*) * e->tab_size;
	new_size = sizeof(char*) * (e->tab_size + new);
	ft_printf("old=%d, new=%d\n", old_size, new_size);
	e->var = (char**)ft_memrealloc(e->var, old_size, new_size);
	e->tab_size += new;
	ft_printf("ICI2\n");
}

void	refresh_sh_var(t_env *e, char *name)
{
	if (ft_strequ(name, "PATH"))
		set_bin_path(e);
	else if (ft_strequ(name, "HOME"))
		set_home_path(e);
}
