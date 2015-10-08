/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_width.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/10 19:43:53 by pbourrie          #+#    #+#             */
/*   Updated: 2015/03/09 22:41:00 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

void	print_width(t_args *args)
{
	char	space_char;

	if (args->param->len < args->param->width)
	{
		space_char = get_space_char(args);
		ft_putnchar(args->param->width - args->param->len, space_char);
		args->total_len += args->param->width - args->param->len;
	}
}

void	set_width(t_args *args)
{
	char	*str;
	char	*zero;
	char	space_char;

	get_width_len(args);
	if (args->param->len < args->param->width)
	{
		space_char = get_space_char(args);
		if (space_char == ' ')
			set_prefix(args);
		zero = ft_strnew(args->param->width - args->param->len);
		ft_memset(zero, space_char, args->param->width - args->param->len);
		if (args->param->minus)
			str = ft_strjoin(args->param->print, zero);
		else
			str = ft_strjoin(zero, args->param->print);
		free(zero);
		free(args->param->print);
		args->param->print = str;
		args->param->len += args->param->width - args->param->len;
		if (space_char == '0')
			set_prefix(args);
	}
	else
		set_prefix(args);
}

void	get_width_len(t_args *args)
{
	if (args->param->type == 'd' || args->param->type == 'f')
		if (args->param->sign == -1 || args->param->plus
			|| args->param->space)
			args->param->len++;
	if (args->param->type == 'x')
		if (args->param->sharp && args->param->sign != 0)
			args->param->len += 2;
	if (args->param->type == 'p')
		args->param->len += 2;
}

char	get_space_char(t_args *args)
{
	if (args->param->zero && !args->param->minus)
	{
		if (!args->param->is_precision &&
			ft_strchr("douxp", args->param->type))
			return ('0');
		else if (!ft_strchr("douxp", args->param->type))
			return ('0');
	}
	return (' ');
}
