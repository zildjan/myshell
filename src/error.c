/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/09 19:55:32 by pbourrie          #+#    #+#             */
/*   Updated: 2016/01/20 23:31:47 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	put_error(int err, char *cmd, char *path, int fd)
{
	if (!cmd)
		cmd = ft_strdup("21sh");
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
		ft_putstr_fd(" Segmentation fault : ", fd);
	else if (ret == SIGBUS)
		ft_putstr_fd(" Bus error : ", fd);
	else if (ret == SIGPIPE)
		ft_putstr_fd(" Broken pipe : ", fd);
	else if (ret == SIGIOT)
		ft_putstr_fd(" I/O error : ", fd);
	else if (ret == SIGFPE)
		ft_putstr_fd(" Floating-point exception : ", fd);
	else if (ret == SIGILL)
		ft_putstr_fd(" Illegal instruction : ", fd);
	else if (ret == SIGABRT)
		ft_putstr_fd(" Aborted : ", fd);
	else if (ret == SIGKILL)
		ft_putstr_fd(" Killed : ", fd);
	else if (ret == SIGQUIT)
		ft_putstr_fd(" Quit : ", fd);
	else
		ft_putstr_fd(" error: ", fd);
	ft_putnbr_fd(ret, fd);
	ft_putstr_fd("  ", fd);
	ft_putendl_fd(path, fd);
}

void	put_cmd_opt_error(char *cmd, char opt, int fd, char *usage)
{
	ft_putstr_fd("21sh: ", fd);
	ft_putstr_fd(cmd, fd);
	ft_putstr_fd(": -", fd);
	ft_putchar_fd(opt, fd);
	ft_putstr_fd(": invalid option\n", fd);
	if (usage)
	{
		ft_putstr_fd(cmd, fd);
		ft_putstr_fd(": usage: ", fd);
		ft_putstr_fd(cmd, fd);
		ft_putstr_fd(" ", fd);
		ft_putstr_fd(usage, fd);
		ft_putstr_fd("\n", fd);
	}
}
