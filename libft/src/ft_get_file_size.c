/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_file_size.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/25 20:23:06 by pbourrie          #+#    #+#             */
/*   Updated: 2015/03/30 21:42:53 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_get_file_size(char *path)
{
	struct stat	buf;

	if (lstat(path, &buf))
		if (stat(path, &buf))
			return (-1);
	return ((long)buf.st_size);
}
