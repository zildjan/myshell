/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_file_mode.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/25 20:23:06 by pbourrie          #+#    #+#             */
/*   Updated: 2015/03/30 21:42:53 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_get_file_mode(char *path)
{
	struct stat	buf;
	int			mode;

	if (lstat(path, &buf))
		if (stat(path, &buf))
			return (-1);
	mode = ((buf.st_mode & S_IRUSR) ? 4 : 0);
	mode += ((buf.st_mode & S_IWUSR) ? 2 : 0);
	mode += ((buf.st_mode & S_IXUSR) ? 1 : 0);
	mode *= 10;
	mode += ((buf.st_mode & S_IRGRP) ? 4 : 0);
	mode += ((buf.st_mode & S_IWGRP) ? 2 : 0);
	mode += ((buf.st_mode & S_IXGRP) ? 1 : 0);
	mode *= 10;
	mode += ((buf.st_mode & S_IROTH) ? 4 : 0);
	mode += ((buf.st_mode & S_IWOTH) ? 2 : 0);
	mode += ((buf.st_mode & S_IXOTH) ? 1 : 0);
	return (mode);
}
