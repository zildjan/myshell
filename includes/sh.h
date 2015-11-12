/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/09 19:55:32 by pbourrie          #+#    #+#             */
/*   Updated: 2015/11/12 22:12:12 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SH_H
# define FT_SH_H

#include <signal.h>
#include <sys/mount.h>

# include "libft.h"
# include "sh_data.h"

/*
**   INI_ENV
*/
t_env		*init_env(void);
void		init_shlvl(t_env *e);

/*
**   GET_ENV
*/
char		*get_env_val(t_env *e, char *name);
int			get_env_id(t_env *e, char *name);
char		*get_env_name(t_env *e, int id);

/*
**   SET_ENV
*/
void		set_new_env_var(t_env *e, char *name, char *val);
void		set_env_var(t_env *e, char *name, char *val);
int			unset_env_var(t_env *e, char *name);
void		resize_env_tab(t_env *e, int new);
void		refresh_sh_var(t_env *e, char *name);

/*
**   BUILTIN_CD
*/
void		builtin_cd(t_env *e);
void		builtin_cd_error(char *path);
char		*builtin_cd_oldpwd(t_env *e);

/*
**   BUILTIN_ENV
*/
void		builtin_env(t_env *e);
void		builtin_env_setenvtab(t_env *e, int opt_i);
char		**builtin_env_malloctab(t_env *e, int opt_i);
int			builtin_env_filltab(t_env *e, char **env, int opt_i);
void		builtin_env_exec(t_env *e, char **env, int i);

/*
**   BUILTIN_SETENV
*/
void		builtin_setenv(t_env *e);
void		builtin_unsetenv(t_env *e);

/*
**   BUILTIN_EXIT
*/
void		builtin_exit(t_env *e);

/*
**   GET_BIN_PATH
*/
void		set_bin_path(t_env *e);
char		*get_cmd_path(t_env *e, char *cmd);

/*
**   HOME
*/
void		set_home_path(t_env *e);
void		parse_home_tilde(t_env *e, int i);

/*
**   GET_CMD
*/
void		get_cmd(t_env *e);

void		parse_cmd_seq(t_env *e);
void		split_cmd_args(t_env *e, char *cmd_seq);

/*
**   PARSE_CMD
*/
void		parse_cmd(t_env *e);
void		parse_cmd_args(t_env *e);


/*
**   EXECUTE
*/
int			process_builtin(t_env *e);
void		process_cmd(t_env *e, char **env);
void		process_fork(t_env *e, char *cmd_path, char **env);

/*
**   PARSE_CMD_VAR
*/
void		parse_env_var(t_env *e, int i);
void		parse_env_var_replace(t_env *e, char *arg, char **cmd);

/*
**   FREE_CMD
*/
void		free_cmd(t_env *e);

/*
**   PROMPT
*/
void		print_prompt(t_env *e);

/*
**   ERROR
*/
void		put_error(int err, char *cmd, char *path);
void		put_sig_error(int ret, char *path);

#endif
