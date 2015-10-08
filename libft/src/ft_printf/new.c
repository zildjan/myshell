/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/03 19:21:40 by pbourrie          #+#    #+#             */
/*   Updated: 2015/03/13 19:34:29 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

t_aparam	*new_aparam(void)
{
	t_aparam	*aparam;

	if ((aparam = (t_aparam*)ft_memalloc(sizeof(t_aparam))) == NULL)
		return (NULL);
	aparam->id = 0;
	aparam->sharp = 0;
	aparam->zero = 0;
	aparam->minus = 0;
	aparam->plus = 0;
	aparam->space = 0;
	aparam->width = 0;
	aparam->precision = -1;
	aparam->is_precision = 0;
	aparam->capital = 0;
	aparam->type = 0;
	aparam->len = 0;
	aparam->sign = 0;
	aparam->modifier = 0;
	aparam->print = NULL;
	aparam->wprint = NULL;
	return (aparam);
}

t_args		*new_args(void)
{
	t_args	*args;

	if ((args = (t_args*)malloc(sizeof(t_args))) == NULL)
		return (NULL);
	args->cur_id = 1;
	return (args);
}

void		init_args(t_args *args, int error, const char *format)
{
	va_copy(args->save, args->cur);
	va_copy(args->temp, args->cur);
	args->pos = 0;
	args->pos_c = 0;
	args->error = error;
	args->total_len = 0;
	args->format_len = ft_strlen(format);
	args->param = NULL;
}

void		free_args(t_args *args)
{
	va_end(args->cur);
	va_end(args->save);
	free(args);
}
