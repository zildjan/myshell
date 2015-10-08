/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/20 19:12:34 by pbourrie          #+#    #+#             */
/*   Updated: 2015/03/16 20:30:26 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "ft_printf_struct.h"

/*
**    FT_PRINTF
*/
void		read_format(const char *format, t_args *args, t_color_tag *color);
int			read_aparam(const char *format, t_args *args, int previous_pos);

/*
**    NEW
*/
t_aparam	*new_aparam(void);
t_args		*new_args(void);
void		init_args(t_args *args, int error, const char *format);
void		free_args(t_args *args);

/*
**    GET_ARG
*/
void		get_arg(int num, int asterisk, t_args *args);
t_ull		get_arg_unbr(t_args *args);
t_ll		get_arg_nbr(t_args *args);
char		get_sign(t_ll nbr);

/*
**    PROCESS_FLAGS
*/
void		get_flags(const char *format, t_args *args);
void		get_modifier(const char *format, t_args *args);
void		get_width_or_id(const char *format, t_args *args);
void		get_precision(const char *format, t_args *args);
void		get_type(const char *format, t_args *args);

/*
**    PROCESS_FLAGS_TOOLS
*/
void		check_modifier(t_args *args, t_modifier temp);
int			is_dollar(const char *format, t_args *args);
int			get_asterisk(const char *format, t_args *args);
int			get_nbr(const char *format, t_args *args);
void		skip_useless_char(const char *format, t_args *args);

/*
**    CHECK_APARAM
*/
void		check_aparam(t_args *args);
void		check_aparam_min(t_args *args);

/*
**    GET_SIGNED_PARAM
*/
void		get_aparam_d(t_args *args);
void		get_aparam_f(t_args *args);

/*
**    GET_UNSIGNED_PARAM
*/
void		get_aparam_u(t_args *args);
void		get_aparam_o(t_args *args);
void		get_aparam_x(t_args *args);
void		get_aparam_p(t_args *args);
void		get_aparam_b(t_args *args);

/*
**    GET_TEXT_PARAM
*/
void		get_aparam_c(t_args *args);
void		get_aparam_s(t_args *args);
void		get_aparam_wc(t_args *args);
void		get_aparam_ws(t_args *args);

/*
**    PRINT
*/
void		print_aparam(t_args *args);
void		get_aparam_print(t_args *args);
void		get_aparam_other(t_args *args);

/*
**    PROCESS_WIDTH
*/
void		set_width(t_args *args);
void		print_width(t_args *args);
void		get_width_len(t_args *args);
char		get_space_char(t_args *args);

/*
**    PROCESS_PRECISION
*/
void		set_nbr_precision(t_args *args, int len);
void		set_prefix(t_args *args);
void		set_prefix_x_o(t_args *args);
void		set_sign(t_args *args);

/*
**    PRINT_UNICODE
*/
void		print_unicode(t_args *args);

#endif
