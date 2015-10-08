/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/20 14:14:07 by pbourrie          #+#    #+#             */
/*   Updated: 2015/03/16 20:23:33 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

int		ft_printf(const char *format, ...)
{
	static int	ft_printf_error = 0;
	t_args		*args;
	t_color_tag	color_tag[CT_NB_TAG];

	if ((args = new_args()) == NULL)
		return (ft_printf_error = -1);
	va_start(args->cur, format);
	init_args(args, ft_printf_error, format);
	if (ACTIVE_FT_PRINTF_COLOR)
		load_color_tags(color_tag);
	read_format(format, args, color_tag);
	free_args(args);
	if (args->error != 0)
		ft_printf_error = -1;
	return ((ft_printf_error != 0) ? -1 : args->total_len);
}

void	read_format(const char *format, t_args *args, t_color_tag *color)
{
	int		add_pos;

	add_pos = 0;
	while (format[args->pos] != 0)
	{
		if (format[args->pos] == CT_TAG_BEGIN && ACTIVE_FT_PRINTF_COLOR)
			add_pos = put_color(format, args->pos, color);
		if (format[args->pos] == '%')
			read_aparam(format, args, -1);
		else if (add_pos == 0)
		{
			ft_putchar(format[args->pos++]);
			args->total_len++;
		}
		if (add_pos)
			args->pos += add_pos;
		add_pos = 0;
	}
}

int		read_aparam(const char *format, t_args *args, int previous_pos)
{
	args->pos_c = args->pos + 1;
	if ((args->param = new_aparam()) == NULL)
		return (args->error = -1);
	previous_pos = -1;
	while (previous_pos != args->pos_c)
	{
		if (args->format_len <= args->pos_c)
		{
			args->pos = args->pos_c;
			return (0);
		}
		previous_pos = args->pos_c;
		get_flags(format, args);
		get_width_or_id(format, args);
		get_precision(format, args);
		get_modifier(format, args);
		skip_useless_char(format, args);
	}
	get_type(format, args);
	print_aparam(args);
	free(args->param);
	args->param = NULL;
	args->pos = args->pos_c;
	return (0);
}
