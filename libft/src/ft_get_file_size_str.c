/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_file_size_str                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/25 19:57:25 by pbourrie          #+#    #+#             */
/*   Updated: 2015/05/11 22:43:37 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_get_file_size_str(char *path)
{
	char	*str;
	long	size;
	char	*nb;

	size = ft_get_file_size(path);
	if (size > 1000000)
	{
		nb = ft_ltoa(size / 1000000);
		str = ft_strjoin(nb, " M");
	}
	else if (size > 1000)
	{
		nb = ft_ltoa(size / 1000);
		str = ft_strjoin(nb, " K");
	}
	else
	{
		nb = ft_ltoa(size);
		str = ft_strjoin(nb, " B");
	}
	free(nb);
	return (str);
}
