/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/10 19:43:53 by pbourrie          #+#    #+#             */
/*   Updated: 2015/03/13 20:50:47 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

void	print_aparam(t_args *args)
{
	check_aparam(args);
	get_aparam_print(args);
	if (args->param->type == 'S' || args->param->type == 'C')
		print_unicode(args);
	else if (args->param->type == 'c')
	{
		if (!args->param->minus)
			print_width(args);
		ft_putchar(*args->param->print);
		if (args->param->minus)
			print_width(args);
	}
	else
		ft_putstr(args->param->print);
	args->total_len += args->param->len;
	if (args->param->print != NULL)
		free(args->param->print);
}

void	get_aparam_print(t_args *args)
{
	if (args->param->type == 'd')
		get_aparam_d(args);
	else if (args->param->type == 'u')
		get_aparam_u(args);
	else if (args->param->type == 'o')
		get_aparam_o(args);
	else if (args->param->type == 'x')
		get_aparam_x(args);
	else if (args->param->type == 'p')
		get_aparam_p(args);
	else if (args->param->type == 'c')
		get_aparam_c(args);
	else if (args->param->type == 's')
		get_aparam_s(args);
	else if (args->param->type == 'S')
		get_aparam_ws(args);
	else if (args->param->type == 'C')
		get_aparam_wc(args);
	else if (args->param->type == 'f')
		get_aparam_f(args);
	else if (args->param->type == 'b')
		get_aparam_b(args);
	else
		get_aparam_other(args);
}

void	get_aparam_other(t_args *args)
{
	args->param->print = ft_strdup(&(args->param->type));
	args->param->len = 1;
	set_width(args);
}
