/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/09 01:28:54 by pbourrie          #+#    #+#             */
/*   Updated: 2016/09/10 02:17:38 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	term_set_tcpgid(t_env *e, pid_t pgid)
{
	if (pgid)
	{
		tcsetpgrp(0, pgid);
		e->tc_pgid = pgid;
		e->last_job = pgid;
	}
	else
	{
		e->tc_pgid = 0;
		if (e->sub)
			tcsetpgrp(0, getpgrp());
		else
			tcsetpgrp(0, e->shell_pgid);
	}
}
