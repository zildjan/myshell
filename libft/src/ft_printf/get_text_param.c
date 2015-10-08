/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_text_param.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/10 19:43:53 by pbourrie          #+#    #+#             */
/*   Updated: 2015/03/13 20:49:38 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

void	get_aparam_c(t_args *args)
{
	char	*str;
	char	nbr;

	get_arg(args->param->id, 0, args);
	str = NULL;
	nbr = 0;
	nbr = va_arg(args->cur, int);
	str = (char*)ft_memalloc(sizeof(char));
	*str = nbr;
	args->param->len = 1;
	args->param->print = str;
}

void	get_aparam_s(t_args *args)
{
	char	*str;

	str = NULL;
	get_arg(args->param->id, 0, args);
	str = ft_strdup(va_arg(args->cur, char*));
	if (str == NULL)
		str = ft_strdup("(null)");
	if (args->param->is_precision)
	{
		if ((size_t)args->param->precision < ft_strlen(str) &&
			args->param->precision > 0)
			args->param->print = ft_strndup(str, args->param->precision);
		else if (args->param->precision == 0)
			args->param->print = ft_strdup("");
		else
			args->param->print = ft_strdup(str);
	}
	else
		args->param->print = ft_strdup(str);
	free(str);
	args->param->len = ft_strlen(args->param->print);
	set_width(args);
}

void	get_aparam_wc(t_args *args)
{
	wchar_t	*str;
	wchar_t	wc;

	get_arg(args->param->id, 0, args);
	str = NULL;
	wc = (wchar_t)va_arg(args->cur, wint_t);
	str = (wchar_t*)ft_memalloc(sizeof(wchar_t));
	*str = wc;
	args->param->wprint = str;
	args->param->len = ft_wcharlen(*args->param->wprint);
}

void	get_aparam_ws(t_args *args)
{
	wchar_t	*str;

	get_arg(args->param->id, 0, args);
	str = ft_wstrdup(va_arg(args->cur, wchar_t*));
	if (str == NULL)
		str = ft_wstrdup(L"(null)");
	if (args->param->is_precision)
	{
		if ((size_t)args->param->precision < ft_wstrlen(str) &&
			args->param->precision > 0)
			args->param->wprint = ft_wstrndup(str, args->param->precision);
		else if (args->param->precision == 0)
			args->param->wprint = ft_wstrdup(L"");
		else
			args->param->wprint = ft_wstrdup(str);
	}
	else
		args->param->wprint = ft_wstrdup(str);
	args->param->len = ft_wstrlen(args->param->wprint);
	free(str);
}
