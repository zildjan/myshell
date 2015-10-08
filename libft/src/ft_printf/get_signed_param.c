/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_signed_param.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/10 19:43:53 by pbourrie          #+#    #+#             */
/*   Updated: 2015/03/09 22:38:13 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

void	get_aparam_d(t_args *args)
{
	char	*str;

	str = NULL;
	str = ft_ltoa(get_arg_nbr(args));
	if (args->param->sign == -1)
		args->param->print = ft_strsub(str, 1, ft_strlen(str));
	else
		args->param->print = ft_strdup(str);
	free(str);
	set_nbr_precision(args, ft_strlen(args->param->print));
	args->param->len = ft_strlen(args->param->print);
	set_width(args);
}

void	get_aparam_f(t_args *args)
{
	char	*str;
	double	nbr;

	str = NULL;
	get_arg(args->param->id, 0, args);
	nbr = va_arg(args->cur, double);
	str = ft_dtoa(nbr, args->param->precision);
	if (nbr < 0)
		args->param->sign = -1;
	else if (nbr > 0)
		args->param->sign = 1;
	else
		args->param->sign = 0;
	if (args->param->sign == -1)
		args->param->print = ft_strsub(str, 1, ft_strlen(str));
	else
		args->param->print = ft_strdup(str);
	free(str);
	set_nbr_precision(args, ft_strlen(args->param->print));
	args->param->len = ft_strlen(args->param->print);
	set_width(args);
}
