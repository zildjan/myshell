/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/09 19:55:32 by pbourrie          #+#    #+#             */
/*   Updated: 2016/01/10 23:08:18 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SH_H
# define FT_SH_H

# include <curses.h>
# include <term.h>
# include <termios.h>
# include <termcap.h>
# include <sys/ioctl.h>

# include <signal.h>
# include <sys/mount.h>
# include <fcntl.h>

# include "libft.h"
# include "sh_data.h"

/*
**   INI_ENV
*/
t_env		*init_env(int argc, char **argv, char **environ);
void		init_env_var(t_env *e, char **environ);
void		init_shlvl(t_env *e);
void		refresh_nb_col(t_env *e);

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
void		builtin_cd_error(t_env *e, char *path);
char		*builtin_cd_oldpwd(t_env *e);

/*
**   BUILTIN_ENV
*/
void		builtin_env(t_env *e);
int			builtin_env_getopt(t_env *e, int *i, int *opt_i, int fd);
void		builtin_env_setenvtab(t_env *e, int opt_i, int i);
void		builtin_env_insertnewent(t_env *e, char **env, int *id, int i);
void		builtin_env_exec(t_env *e, char **env, int i);

/*
**   BUILTIN_ENV_TOOLS
*/
char		**builtin_env_malloctab(t_env *e, int opt_i);
int			builtin_env_filltab(t_env *e, char **env, int opt_i);

/*
**   BUILTIN_SETENV
*/
void		builtin_setenv(t_env *e);
void		builtin_unsetenv(t_env *e);
int			builtin_setenv_check(char *str, int egual, int identifier);

/*
**   BUILTIN_EXIT
*/
void		builtin_exit(t_env *e);
void		builtin_exit_all(t_env *e, int status);

/*
**   BUILTIN_HISTORY
*/
void		history_print(t_env *e);

/*
**   GET_BIN_PATH
*/
void		set_bin_path(t_env *e);
char		*get_cmd_path(t_env *e, char *cmd);

/*
**   HOME
*/
void		set_home_path(t_env *e);

/*
**   GET_CMD
*/
void		get_cmd(t_env *e);
int			get_cmd_end(t_env *e, char type);
int			get_input_line(t_env *e, int eof_exit);
void		resize_input_line(t_env *e);

int			process_all_key(t_env *e, int ret, char *buf, int eof_exit);

int			process_option_key(t_env *e, int ret, char *buf, int eof_exit);
int			process_break_key(t_env *e, int ret, char *buf);

int			process_cursor_key(t_env *e, int ret, char *buf);
int			process_cursor2_key(t_env *e, int ret, char *buf);
int			process_home_end_key(t_env *e, int ret, char *buf);
int			process_prev_word_key(t_env *e, int ret, char *buf);
int			process_next_word_key(t_env *e, int ret, char *buf);

int			process_edition_key(t_env *e, int ret, char *buf);
int			process_histo_up_key(t_env *e, char *buf);
int			process_histo_down_key(t_env *e, char *buf);

int			get_term_line_input(t_env *e, int eof_exit);
void		get_input_chars(t_env *e, char *buf);
void		get_input_char(t_env *e, char c);
void		delete_input_char(t_env *e);
void		delete_input_nchar(t_env *e, int n);
void		backdelete_input_char(t_env *e, char no_mem);

void		move_cursor_back(t_env *e, char delete, int i);

void		cut_input_line(t_env *e);
void		paste_input_line(t_env *e);

void		switch_to_histo(t_env *e);

int			move_cursor_right(t_env *e);
int			move_cursor_left(t_env *e);
int			is_end_of_line(t_env *e, int cur);
int			ft_outc(int c);

void		close_line_edition(t_env *e);

/*
**   HISTORY
*/
void		history_init(t_env *e);
void		history_load(t_env *e);
void		history_add(t_env *e, char escape);
void		history_save_ent(t_env *e);
void		history_add_to_mem(t_env *e, char *line);

/*
**   PARSE_CMD
*/
void		parse_cmd(t_env *e);

void		parse_add_arg(t_env *e, t_parse *p);
void		parse_add_cmd(t_env *e, t_parse *p, char sep);
int			parse_add_redirec(t_env *e, t_parse *p);
void		parse_get_redirec_type(t_env *e, t_parse *p);
void		new_redirec(t_env *e, char *file, int type, int fd);

void		check_arg_buf_size(t_parse *p);
int			is_aspace(char c);
void		parse_cmd_cleanline(t_env *e);
void		realloc_buffer(t_parse *p, int add);
char		*dup_arg(char *buf);

/*
**   PARSE_CMD_VAR
*/
void		parse_var_expansion(t_env *e, t_parse *p);
void		parse_var_expansion2(t_env *e, t_parse *p, char *arg, char *new);
void		parse_tilde_expansion(t_env *e, t_parse *p);

/*
**   EXECUTE
*/
int			process_builtin(t_env *e);
void		process_cmd(t_env *e);
void		process_bin(t_env *e, char **env);
void		process_fork(t_env *e, char *cmd_path, char **env);

/*
**   WAIT
*/
void		process_wait(t_env *e, int pid, int job);
void		process_wait_error(t_env *e, int ret, int job);
void		process_wait_list(t_env *e);

/*
**   HEREDOC
*/
int			read_heredoc(t_env *e, t_redir *redir);
void		heredoc_assign(t_env *e, t_redir *redir);
void		get_heredoc(t_env *e, char *eof);
void		get_heredoc_p2(t_env *e, char *eof);
void		get_heredoc_p3(t_env *e, int *ret, t_hdoc *hdoc);

/*
**   REDIRECTIONS
*/
int			redirec_open(t_env *e);
void		redirec_assign(t_env *e);
void		redirec_close(t_env *e, int cid);
int			redirec_open_files(t_redir *redir);

int			redirec_open_dupfd(t_redir *redir);
void		redirec_assign_dupfd(t_redir *redir);
int			getcurstdfd(t_env *e, int fd);
void		open_file_error(char *path, int type);

/*
**   PIPE
*/
int			pipe_new(t_env *e, t_redir *redir);
void		pipe_assign(t_env *e, t_redir *redir);
void		pipe_close(t_env *e, int cid);

/*
**   TERM
*/
void		term_init(t_env *e);
void		term_backup(t_env *e);
void		term_restore(t_env *e);
void		term_restore_back(t_env *e);
void		term_restore_backup(struct termios *back);

/*
**   TERM KEY
*/
void		term_load_info(t_env *e);
void		term_load_key_default(t_env *e);
void		term_load_key_default2(t_env *e);
void		term_load_key(t_env *e);
void		term_load_key2(t_env *e);

/*
**   JOBS
*/
void		jobs_add(t_env *e, int pid);
void		jobs_continue(t_env *e);
void		jobs_remove(t_env *e, int pid);
void		jobs_list(t_env *e);
int			jobs_count(t_env *e, int pid);

/*
**   PROMPT
*/
void		print_prompt(t_env *e);
char		*ft_get_up_dir(char *path, int level);

/*
**   FREE_ENV
*/
void		free_env(t_env *e);
void		free_history(t_env *e);
void		kill_jobs(t_env *e);
void		free_path_and_env(t_env *e);

/*
**   FREE_CMD
*/
void		free_cmd(t_env *e);
void		free_cmd_redirec(t_env *e, int i);
void		free_heredoc(t_env *e, int cid);

/*
**   ERROR
*/
void		put_error(int err, char *cmd, char *path, int fd);
void		put_sig_error(int ret, char *path, int fd);

/*
**   SIGNAL
*/
void		catch_signal(void);
void		sig_handler(t_env *e, int signum);
void		sig_mediator(int signum);

#endif
