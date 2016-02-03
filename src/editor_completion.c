/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_completion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/01 23:00:22 by pbourrie          #+#    #+#             */
/*   Updated: 2016/02/03 02:04:07 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	editor_completion(t_env *e)
{

	while (e->cur < e->line_len)
		move_cursor_right(e);
	ft_putchar('\n');

	completion_update(e);

	int i = -1;
	while (e->compl->poss[++i])
	{
		ft_putstr(e->compl->poss[i]);
		ft_putstr("  ");
	}
	ft_putchar('\n');

	print_prompt(e);
	ft_putstr(e->line);
}
