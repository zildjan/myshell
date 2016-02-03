/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_escape_chars.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/03 01:48:57 by pbourrie          #+#    #+#             */
/*   Updated: 2016/02/03 01:52:13 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_escape_chars(char *str, char *c)
{
	char	*new;
	int		i;
	int		i2;

	i = -1;
	i2 = 0;
	while (str[++i])
		if (ft_strchr(c, str[i]))
			i2++;
	new = ft_strnew(i + i2);
	i = -1;
	i2 = 0;
	while (str[++i])
	{
		if (ft_strchr(c, str[i]))
			new[i2++] = '\\';
		new[i2++] = str[i];
	}
	return (new);
}
