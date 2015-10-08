/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_flags_tools.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/20 14:14:07 by pbourrie          #+#    #+#             */
/*   Updated: 2015/03/13 19:36:00 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

void	check_modifier(t_args *args, t_modifier temp)
{
	if (temp != NONE)
	{
		if (temp != HH && temp != H)
			args->param->modifier = temp;
		else if ((temp == HH || temp == H) && args->param->modifier == NONE)
			args->param->modifier = temp;
		if (temp == LL || temp == HH)
			args->pos_c++;
		args->pos_c++;
	}
}

int		is_dollar(const char *format, t_args *args)
{
	int		i;

	i = 1;
	while (ft_isdigit(format[args->pos_c + i]))
		i++;
	if (format[args->pos_c + i] == '$')
		return (1);
	return (0);
}

int		get_asterisk(const char *format, t_args *args)
{
	int		nb;

	nb = 0;
	args->pos_c++;
	if (format[args->pos_c] >= '1' && format[args->pos_c] <= '9'
		&& is_dollar(format, args))
	{
		get_arg(get_nbr(format, args), 1, args);
		nb = va_arg(args->temp, int);
		args->pos_c++;
	}
	else
	{
		get_arg(0, 0, args);
		nb = va_arg(args->cur, int);
	}
	return (nb);
}

int		get_nbr(const char *format, t_args *args)
{
	int		i;
	int		nbr;
	char	*str;

	i = 1;
	nbr = 0;
	while (ft_isdigit(format[args->pos_c + i]))
		i++;
	str = ft_strsub(format, args->pos_c, i);
	nbr = ft_atoi(str);
	free(str);
	args->pos_c += i;
	return (nbr);
}

void	skip_useless_char(const char *format, t_args *args)
{
	if (format[args->pos_c] == '\'')
		args->pos_c++;
	else if (format[args->pos_c] == '\\')
		args->pos_c++;
}
