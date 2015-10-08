/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_unsigned_param.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/10 19:43:53 by pbourrie          #+#    #+#             */
/*   Updated: 2015/03/10 22:11:10 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

void	get_aparam_u(t_args *args)
{
	char	*str;

	str = NULL;
	str = ft_ultoa(get_arg_unbr(args));
	args->param->print = str;
	set_nbr_precision(args, ft_strlen(args->param->print));
	args->param->len = ft_strlen(args->param->print);
	set_width(args);
}

void	get_aparam_o(t_args *args)
{
	char	*str;

	str = NULL;
	str = ft_ultoa_base(get_arg_unbr(args), 8);
	args->param->print = str;
	set_prefix_x_o(args);
	set_nbr_precision(args, ft_strlen(args->param->print));
	args->param->len = ft_strlen(args->param->print);
	set_width(args);
}

void	get_aparam_x(t_args *args)
{
	char	*str;

	str = NULL;
	str = ft_ultoa_base(get_arg_unbr(args), 16);
	args->param->print = str;
	set_nbr_precision(args, ft_strlen(args->param->print));
	args->param->len = ft_strlen(args->param->print);
	set_width(args);
	if (args->param->capital)
		ft_strtoupper(args->param->print);
	args->param->len = ft_strlen(args->param->print);
}

void	get_aparam_p(t_args *args)
{
	args->param->modifier = L;
	get_aparam_x(args);
}

void	get_aparam_b(t_args *args)
{
	char	*str;

	str = NULL;
	str = ft_ultoa_base(get_arg_unbr(args), 2);
	args->param->print = str;
	set_nbr_precision(args, ft_strlen(args->param->print));
	args->param->len = ft_strlen(args->param->print);
	set_width(args);
}
