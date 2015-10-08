/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_struct.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/20 19:12:34 by pbourrie          #+#    #+#             */
/*   Updated: 2015/03/13 19:33:41 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_STRUCT_H
# define FT_PRINTF_STRUCT_H

typedef enum	e_modifier
{
	NONE,
	HH,
	H,
	L,
	LL,
	J,
	T,
	Z
}				t_modifier;

typedef struct	s_aparam
{
	int			id;
	char		sharp;
	char		zero;
	char		minus;
	char		plus;
	char		space;
	int			width;
	int			precision;
	char		is_precision;
	char		capital;
	char		type;
	int			len;
	t_modifier	modifier;
	char		sign;
	char		*print;
	wchar_t		*wprint;
}				t_aparam;

typedef struct	s_args
{
	va_list		save;
	va_list		cur;
	va_list		temp;
	int			cur_id;
	int			pos;
	int			pos_c;
	int			total_len;
	int			error;
	int			format_len;
	t_aparam	*param;
}				t_args;

#endif
