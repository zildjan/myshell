/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/07 19:30:05 by pbourrie          #+#    #+#             */
/*   Updated: 2016/09/08 00:02:36 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	free_env(t_env *e)
{
	free_history(e);
	if (e->cmd)
		free_cmd(e);
	free_path_and_env(e);
	free_hash_table(e);
	completion_free(e);
	free_alias(e);
	free_env_var(e);
	free(e);
}

void	free_env_var(t_env *e)
{
	if (e->line)
		free(e->line);
	if (e->home)
		free(e->home);
	if (e->home_dir)
		free(e->home_dir);
	if (e->pwd)
		free(e->pwd);
	if (e->clipboard)
		free(e->clipboard);
	if (e->histo_file)
		free(e->histo_file);
	if (e->term_name)
		free(e->term_name);
	if (e->term)
		free(e->term);
	if (e->term_back)
		free(e->term_back);
	if (e->prompt)
		free(e->prompt);
}
