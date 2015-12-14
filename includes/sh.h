/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/09 19:55:32 by pbourrie          #+#    #+#             */
/*   Updated: 2015/11/13 21:51:04 by pbourrie         ###   ########.fr       */
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
t_env		*init_env(int argc, char **argv, char **environ);
void		init_env_var(t_env *e, char **environ);
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
int			builtin_env_getopt(t_env *e, int *i, int *opt_i);
void		builtin_env_setenvtab(t_env *e, int opt_i, int i);
void		builtin_env_insertnewent(t_env *e, char **env, int *id, int i);
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
void		builtin_exit_jobs(t_env *e, int status);

/*
**   GET_BIN_PATH
*/
void		set_bin_path(t_env *e);
char		*get_cmd_path(t_env *e, char *cmd);

/*
**   HOME
*/
void		set_home_path(t_env *e);
void		parse_home_tilde(t_env *e, int id_cmd, int id_arg);

/*
**   GET_CMD
*/
void		get_cmd(t_env *e);

//void		parse_cmd_seq(t_env *e);
//void		split_cmd_pipes(t_env *e, char *cmd);
//void		split_cmd_args(t_env *e, char **pipes);

/*
**   PARSE_CMD
*/
void		parse_cmd(t_env *e);

void		parse_add_arg(t_env *e, t_parse *p);
void		parse_add_cmd(t_env *e, t_parse *p, char sep);
int			parse_add_redirec(t_env *e, t_parse *p);
void		parse_get_redirec_type(t_env *e, t_parse *p);
void		new_redirec(t_env *e, char *file, int type, int fd);

int			is_aspace(char c);
void		parse_cmd_cleanline(t_env *e);

void		parse_cmd_args(t_env *e);

/*
**   EXECUTE
*/
int			process_builtin(t_env *e);
void		process_cmd(t_env *e);
void		process_bin(t_env *e, char **env);
void		process_fork(t_env *e, char *cmd_path, char **env);
void		process_wait(t_env *e, int pid, int job);

/*
**   REDIRECTIONS
*/


/*
**   PIPE
*
void		pipe_new(t_env *e);
void		pipe_assign(t_env *e);
void		pipe_close(t_env *e);
// */
/*
**   JOBS
*/
void		jobs_add(t_env *e, int pid);
void		jobs_continue(t_env *e);
void		jobs_remove(t_env *e, int pid);
void		jobs_list(t_env *e);
int			jobs_count(t_env *e, int pid);
void		jobs_exit(t_env *e);

/*
**   PARSE_CMD_VAR
*/
void		parse_env_var(t_env *e, int id_cmd, int id_arg);
void		parse_env_var_replace(t_env *e, char *arg, char **cmd);

/*
**   FREE_CMD
*/
void		free_cmd(t_env *e);
void		free_cmd_redirec(t_env *e, int i);

/*
**   PROMPT
*/
void		print_prompt(t_env *e);

/*
**   ERROR
*/
void		put_error(int err, char *cmd, char *path);
void		put_sig_error(int ret, char *path);

/*
**   SIGNAL
*/
void		catch_signal(void);
void		sig_handler(t_env *e, int signum);
void		sig_mediator(int signum);

#endif
