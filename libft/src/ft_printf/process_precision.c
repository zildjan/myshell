/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_precision.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/10 19:43:53 by pbourrie          #+#    #+#             */
/*   Updated: 2015/03/10 22:17:45 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

void	set_nbr_precision(t_args *args, int len)
{
	char	*str;
	char	*zero;

	if (args->param->sign == 0 && args->param->precision == 0)
	{
		free(args->param->print);
		args->param->print = ft_strdup("");
	}
	if (args->param->sign == 0 && args->param->sharp
		&& args->param->type == 'o')
	{
		free(args->param->print);
		args->param->print = ft_strdup("0");
	}
	if (len < args->param->precision)
	{
		zero = ft_strnew(args->param->precision - len);
		ft_memset(zero, '0', args->param->precision - len);
		str = ft_strjoin(zero, args->param->print);
		free(zero);
		free(args->param->print);
		args->param->print = str;
	}
}

void	set_prefix(t_args *args)
{
	if (args->param->type == 'd' || args->param->type == 'f')
		set_sign(args);
	else if (args->param->type == 'x' || args->param->type == 'p')
		set_prefix_x_o(args);
}

void	set_prefix_x_o(t_args *args)
{
	char	*str;

	str = NULL;
	if (args->param->type == 'p' ||
		(args->param->sharp && args->param->sign == 1))
	{
		if (args->param->type == 'o')
			str = ft_strjoin("0", args->param->print);
		else
			str = ft_strjoin("0x", args->param->print);
		free(args->param->print);
		args->param->print = str;
	}
}

void	set_sign(t_args *args)
{
	char *str;

	if (args->param->sign == -1)
	{
		str = ft_strjoin("-", args->param->print);
		free(args->param->print);
		args->param->print = str;
	}
	str = NULL;
	if ((args->param->plus || args->param->space)
		&& args->param->sign != -1)
	{
		if (args->param->plus)
			str = ft_strjoin("+", args->param->print);
		else
			str = ft_strjoin(" ", args->param->print);
		free(args->param->print);
		args->param->print = str;
	}
}
