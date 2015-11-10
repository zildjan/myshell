/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/09 19:55:32 by pbourrie          #+#    #+#             */
/*   Updated: 2015/11/10 21:32:22 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	put_error(int err, char *cmd, char *path)
{
	if (!cmd)
		cmd = ft_strdup("minishell");
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	free(cmd);
	if (err == ERRACCES)
		ft_putstr_fd("Permission denied: ", 2);
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
	else if (ret == SIGPIPE)
		ft_putstr_fd(" broken pipe ", 2);
	else if (ret == SIGIOT)
		ft_putstr_fd(" I/O error ", 2);
	else if (ret == SIGFPE)
		ft_putstr_fd(" Floating-point exception ", 2);
	else if (ret == SIGILL)
		ft_putstr_fd(" Illegal instruction ", 2);
	else if (ret == SIGABRT)
		ft_putstr_fd(" aborted ", 2);
	else if (ret == SIGKILL)
		ft_putstr_fd(" killed ", 2);
	else if (ret == SIGINT)
		ft_putstr_fd(" interruped ", 2);
	else if (ret == SIGQUIT)
		ft_putstr_fd(" quit ", 2);
	else
		ft_putstr_fd(" error: ", 2);
	ft_putendl_fd(path, 2);
}
