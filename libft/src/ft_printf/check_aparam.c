/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_aparam.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/10 19:43:53 by pbourrie          #+#    #+#             */
/*   Updated: 2015/03/09 22:36:37 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

void	check_aparam(t_args *args)
{
	check_aparam_min(args);
	if (ft_strchr("DOU", args->param->type))
	{
		args->param->modifier = L;
		args->param->type = ft_tolower(args->param->type);
	}
	if (args->param->type == 'i')
		args->param->type = 'd';
	if (args->param->type == 'X')
	{
		args->param->type = 'x';
		args->param->capital = 1;
	}
	if (args->param->modifier == L)
	{
		if (args->param->type == 's')
			args->param->type = 'S';
		else if (args->param->type == 'c')
			args->param->type = 'C';
	}
}

void	check_aparam_min(t_args *args)
{
	if (args->param->type == 'F')
	{
		args->param->type = 'f';
		args->param->capital = 1;
	}
	if (args->param->width < 0)
	{
		args->param->minus = 1;
		args->param->width *= -1;
	}
	if (args->param->precision < 0)
	{
		if (args->param->type == 'f')
			args->param->precision = 6;
		else
			args->param->precision = 1;
		args->param->is_precision = 0;
	}
}
