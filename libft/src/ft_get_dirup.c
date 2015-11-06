/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_dirup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/06 20:43:53 by pbourrie          #+#    #+#             */
/*   Updated: 2015/11/06 20:45:32 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_get_dirup(char *path)
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
	return (ft_strsub(path, 0, i + 1));
}
