/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_basename.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/01 18:33:40 by pbourrie          #+#    #+#             */
/*   Updated: 2014/12/17 20:16:50 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_get_basename(char *path)
{
	int	i;
	int	len;

	len = 0;
	i = ft_strlen(path);
	while (i >= 0)
	{
		if (path[i] == '/')
			break ;
		len++;
		i--;
	}
	return (ft_strsub(path, i + 1, len));
}
