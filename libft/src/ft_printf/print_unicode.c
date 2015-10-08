/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_unicode.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/24 22:26:44 by pbourrie          #+#    #+#             */
/*   Updated: 2015/03/13 20:47:00 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

void	print_unicode(t_args *args)
{
	if (!args->param->minus)
		print_width(args);
	if (args->param->type == 'C')
	{
		if (ft_putwchar(*args->param->wprint) == -1)
			args->error = -1;
	}
	else if (args->param->type == 'S')
	{
		if (ft_putwstr(args->param->wprint) == -1)
			args->error = -1;
	}
	if (args->param->minus)
		print_width(args);
	if (args->param->wprint != NULL)
		free(args->param->wprint);
}
