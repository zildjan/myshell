/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/09 19:55:32 by pbourrie          #+#    #+#             */
/*   Updated: 2015/11/13 19:51:42 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	put_error(int err, char *cmd, char *path, int fd)
{
	if (!cmd)
		cmd = ft_strdup("minishell");
	ft_putstr_fd(cmd, fd);
	ft_putstr_fd(": ", fd);
	free(cmd);
	if (err == ERRACCES)
		ft_putstr_fd("Permission denied: ", fd);
	else if (err == ERRNOENT)
		ft_putstr_fd("no such file or directory: ", fd);
	else if (err == ERRNOTDIR)
		ft_putstr_fd("not a directory: ", fd);
	else if (err == ERRISDIR)
		ft_putstr_fd("is a directory: ", fd);
	else if (err == ERRNOCMD)
		ft_putstr_fd("command not found: ", fd);
	else if (err == ERREXEFORM)
		ft_putstr_fd("Exec format error: ", fd);
	else
		ft_putstr_fd("error: ", fd);
	ft_putendl_fd(path, fd);
}

void	put_sig_error(int ret, char *path, int fd)
{
	if (ret == SIGSEGV)
		ft_putstr_fd(" segmentation fault : ", fd);
	else if (ret == SIGBUS)
		ft_putstr_fd(" bus error : ", fd);
	else if (ret == SIGPIPE)
		ft_putstr_fd(" broken pipe : ", fd);
	else if (ret == SIGIOT)
		ft_putstr_fd(" I/O error : ", fd);
	else if (ret == SIGFPE)
		ft_putstr_fd(" Floating-point exception : ", fd);
	else if (ret == SIGILL)
		ft_putstr_fd(" Illegal instruction : ", fd);
	else if (ret == SIGABRT)
		ft_putstr_fd(" aborted : ", fd);
	else if (ret == SIGKILL)
		ft_putstr_fd(" killed : ", fd);
	else if (ret == SIGQUIT)
		ft_putstr_fd(" quit : ", fd);
	else
		ft_putstr_fd(" error: ", fd);
	ft_putnbr_fd(ret, fd);
	ft_putstr_fd("  ", fd);
	ft_putendl_fd(path, fd);
}
