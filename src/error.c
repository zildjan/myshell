/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/09 19:55:32 by pbourrie          #+#    #+#             */
/*   Updated: 2015/10/09 21:27:14 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	put_error(int err, char *path)
{
	ft_putstr_fd("minishell: ", 2);
	if (err == ERRACCES)
		ft_putstr_fd("permission denied: ", 2);
	else if (err == ERRNOENT)
		ft_putstr_fd("no such file or directory: ", 2);
	else if (err == ERRNOTDIR)
		ft_putstr_fd("not a directory: ", 2);
	else if (err == ERRNOCMD)
		ft_putstr_fd("command not found: ", 2);
	else if (err == ERREXEFORM)
		ft_putstr_fd("Exec format error: ", 2);
	else
		ft_putstr_fd("error: ", 2);
	ft_putendl_fd(path, 2);
}

void	put_sig_error(int pid, int ret, char *path)
{
	ft_putstr_fd("[*]   ", 2);
	ft_putnbr_fd(pid, 2);
	if (ret == SIGSEGV)
		ft_putstr_fd(" segmentation fault ", 2);
	else if (ret == SIGBUS)
		ft_putstr_fd(" bus error ", 2);
	else
		ft_putstr_fd("error: ", 2);
	ft_putendl_fd(path, 2);
}
