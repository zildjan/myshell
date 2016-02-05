/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_lfile_type.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/25 20:23:06 by pbourrie          #+#    #+#             */
/*   Updated: 2016/02/06 00:49:03 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	ft_get_lfile_type(char *path)
{
	struct stat	buf;

	if (stat(path, &buf))
		return (-1);
	if (S_ISREG(buf.st_mode))
		return ('-');
	else if (S_ISDIR(buf.st_mode))
		return ('d');
	else if (S_ISFIFO(buf.st_mode))
		return ('p');
	else if (S_ISCHR(buf.st_mode))
		return ('c');
	else if (S_ISBLK(buf.st_mode))
		return ('b');
	else if (S_ISSOCK(buf.st_mode))
		return ('s');
	else if (S_ISLNK(buf.st_mode))
		return ('l');
	else if (S_ISWHT(buf.st_mode))
		return ('w');
	else
		return ('?');
}
