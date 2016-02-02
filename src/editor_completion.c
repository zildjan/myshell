/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_completion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/01 23:00:22 by pbourrie          #+#    #+#             */
/*   Updated: 2016/02/02 01:31:32 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	editor_completion(t_env *e)
{
	int		type;
	t_poss	*poss;

	while (e->cur < e->line_len)
		move_cursor_right(e);
	ft_putchar('\n');

	type = editor_completion_gettype(e);
	poss = completion_get_poss(e, type);

	while (poss)
	{
		ft_putstr(poss->str);
		ft_putstr("  ");
		poss = poss->next;
	}

	ft_putchar('\n');
	print_prompt(e);
	ft_putstr(e->line);
}

int		editor_completion_gettype(t_env *e)
{
	int		cur;

	cur = 0;
	if (e->cur)
		cur = e->cur - 1;
	while (cur && ft_isalnum(e->line[cur]))
		cur--;
	while (cur && is_aspace(e->line[cur]))
		cur--;
	if (cur == 0)
		return (0);
	return (1);
}
