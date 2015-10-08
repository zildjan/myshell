/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_argc                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/03 20:08:00 by pbourrie          #+#    #+#             */
/*   Updated: 2015/03/02 21:23:46 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

void		get_arg(int num, int asterisk, t_args *args)
{
	int	i;

	i = 0;
	if (num == 0)
	{
		args->cur_id++;
	}
	else if (asterisk == 0)
	{
		args->cur_id = num;
		va_end(args->cur);
		va_copy(args->cur, args->save);
		while (++i < num)
			va_arg(args->cur, void*);
	}
	else
	{
		va_end(args->temp);
		va_copy(args->temp, args->save);
		while (++i < num)
			va_arg(args->temp, void*);
	}
}

t_ull		get_arg_unbr(t_args *args)
{
	unsigned long long	nbr;

	nbr = 0;
	get_arg(args->param->id, 0, args);
	if (args->param->modifier == LL)
		nbr = va_arg(args->cur, unsigned long long);
	else if (args->param->modifier == L)
		nbr = va_arg(args->cur, unsigned long);
	else if (args->param->modifier == HH)
		nbr = (unsigned char)va_arg(args->cur, unsigned int);
	else if (args->param->modifier == H)
		nbr = (unsigned short)va_arg(args->cur, unsigned int);
	else if (args->param->modifier == J)
		nbr = (uintmax_t)va_arg(args->cur, uintmax_t);
	else if (args->param->modifier == Z)
		nbr = (size_t)va_arg(args->cur, size_t);
	else
		nbr = va_arg(args->cur, unsigned int);
	if (nbr > 0)
		args->param->sign = 1;
	return (nbr);
}

t_ll		get_arg_nbr(t_args *args)
{
	long long	nbr;

	nbr = 0;
	get_arg(args->param->id, 0, args);
	if (args->param->modifier == LL)
		nbr = va_arg(args->cur, long long);
	else if (args->param->modifier == L)
		nbr = va_arg(args->cur, long);
	else if (args->param->modifier == HH)
		nbr = (char)va_arg(args->cur, int);
	else if (args->param->modifier == H)
		nbr = (short)va_arg(args->cur, int);
	else if (args->param->modifier == J)
		nbr = (intmax_t)va_arg(args->cur, intmax_t);
	else if (args->param->modifier == Z)
		nbr = (size_t)va_arg(args->cur, size_t);
	else
		nbr = va_arg(args->cur, int);
	args->param->sign = get_sign(nbr);
	return (nbr);
}

char		get_sign(t_ll nbr)
{
	if (nbr > 0)
		return (1);
	else if (nbr < 0)
		return (-1);
	else
		return (0);
}
