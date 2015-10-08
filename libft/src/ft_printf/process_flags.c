/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_flags.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/20 14:14:07 by pbourrie          #+#    #+#             */
/*   Updated: 2015/03/13 19:48:15 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

void	get_flags(const char *format, t_args *args)
{
	if (format[args->pos_c] == '#')
		args->param->sharp = 1;
	else if (format[args->pos_c] == '0')
		args->param->zero = 1;
	else if (format[args->pos_c] == '-')
		args->param->minus = 1;
	else if (format[args->pos_c] == '+')
		args->param->plus = 1;
	else if (format[args->pos_c] == ' ')
		args->param->space = 1;
	else
		args->pos_c--;
	args->pos_c++;
}

void	get_modifier(const char *format, t_args *args)
{
	t_modifier	modif_temp;

	modif_temp = NONE;
	if (format[args->pos_c] == 'h' && format[args->pos_c + 1] == 'h')
		modif_temp = HH;
	else if (format[args->pos_c] == 'l' && format[args->pos_c + 1] == 'l')
		modif_temp = LL;
	else if (format[args->pos_c] == 'h')
		modif_temp = H;
	else if (format[args->pos_c] == 'l')
		modif_temp = L;
	else if (format[args->pos_c] == 'j')
		modif_temp = J;
	else if (format[args->pos_c] == 't')
		modif_temp = T;
	else if (format[args->pos_c] == 'z')
		modif_temp = Z;
	check_modifier(args, modif_temp);
}

void	get_width_or_id(const char *format, t_args *args)
{
	if (format[args->pos_c] == '*')
		args->param->width = get_asterisk(format, args);
	else if (format[args->pos_c] >= '1' && format[args->pos_c] <= '9')
	{
		if (is_dollar(format, args))
		{
			args->param->id = get_nbr(format, args);
			args->pos_c++;
		}
		else
			args->param->width = get_nbr(format, args);
	}
}

void	get_precision(const char *format, t_args *args)
{
	if (format[args->pos_c] == '.')
	{
		args->pos_c++;
		args->param->is_precision = 1;
		if (format[args->pos_c] == '*')
			args->param->precision = get_asterisk(format, args);
		else if (ft_isdigit(format[args->pos_c]))
			args->param->precision = get_nbr(format, args);
		else
			args->param->precision = 0;
	}
}

void	get_type(const char *format, t_args *args)
{
	args->param->type = format[args->pos_c];
	args->pos_c++;
}
