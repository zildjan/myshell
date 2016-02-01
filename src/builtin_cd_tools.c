/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/26 18:47:14 by pbourrie          #+#    #+#             */
/*   Updated: 2016/02/01 01:03:57 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	builtin_cd_clean_path(char *new_pwd, int i)
{
	i = 0;
	while (new_pwd[i])
	{
		if (new_pwd[i] == '.' && new_pwd[i + 1] == '/')
			ft_strcpy(new_pwd + i, new_pwd + i + 2);
		else if (new_pwd[i] == '.' && new_pwd[i + 1] == '.'
				&& new_pwd[i + 2] != '.')
			i += 2;
		else
			i++;
	}
	i = -1;
	while (new_pwd[++i])
		while (new_pwd[i] == '/' && new_pwd[i + 1] == '/')
			ft_strcpy(new_pwd + i, new_pwd + i + 1);
	builtin_cd_parse_dotdot(new_pwd, &i, 0, 0);
	if (i < 0)
		i = 0;
	if (new_pwd[i - 1] == '/' && i > 1)
		new_pwd[i - 1] = 0;
	else if (i == 0)
	{
		new_pwd[0] = '/';
		new_pwd[1] = 0;
	}
}

void	builtin_cd_parse_dotdot(char *new_pwd, int *i, int last, int len)
{
	last = 0;
	len = 0;
	*i = -1;
	while (new_pwd[++*i])
	{
		if (new_pwd[*i] == '/')
		{
			if (len == 2 && new_pwd[*i - 2] == '.' && new_pwd[*i - 1] == '.')
			{
				last = *i - 4;
				if (last < 0)
					last = 0;
				while (new_pwd[last] && new_pwd[last] != '/')
					last--;
				ft_strcpy(new_pwd + last, new_pwd + *i);
				*i = ft_strlen(new_pwd);
				while (new_pwd[++*i])
					new_pwd[*i] = 0;
				*i = last;
			}
			len = 0;
		}
		else
			len++;
	}
}
