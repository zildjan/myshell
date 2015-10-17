/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/09 19:55:32 by pbourrie          #+#    #+#             */
/*   Updated: 2015/10/09 21:25:29 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SH_H
# define FT_SH_H

#include <signal.h>

# include "libft.h"
# include "sh_data.h"

/*
**   INI_ENV
*/
t_env		*init_env(void);

/*
**   GET_ENV
*/
char		*get_env_val(t_env *e, char *name);
int			get_env_id(t_env *e, char *name);

/*
**   GET_BIN_PATH
*/
void		set_bin_path(t_env *e);
char		*get_cmd_path(t_env *e, char *cmd);

/*
**   GET_CMD
*/
void		get_cmd(t_env *e);
void		get_cmd_seq(t_env *e);
void		get_cmd_opts(t_env *e, char **cmd_seq);

/*
**   PARSE_CMD
*/
void		parse_cmd_seq(t_env *e);
void		parse_cmd(t_env *e);

int			process_builtin(t_env *e);
void		process_cmd(t_env *e);

/*
**   FREE_CMD
*/
void		free_cmd(t_env *e);

/*
**   PROMPT
*/
void		print_prompt(void);

#endif
