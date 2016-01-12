/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdupcat.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/11 19:16:46 by pbourrie          #+#    #+#             */
/*   Updated: 2016/01/12 17:41:23 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdupcat(char *s1, char const *s2)
{
	char	*str;

	str = NULL;
	if (s1 && s2)
	{
		if (!(str = ft_strnew(ft_strlen(s1) + ft_strlen(s2))))
			return (NULL);
		str = ft_strcpy(str, s1);
		str = ft_strcat(str, s2);
		free(s1);
	}
	else if (s1)
	{
		str = ft_strnew(ft_strlen(s1));
		str = ft_strcpy(str, s1);
		free(s1);
	}
	else if (s2)
	{
		str = ft_strnew(ft_strlen(s2));
		str = ft_strcpy(str, s2);
	}
	if (str)
		return (str);
	return (NULL);
}
