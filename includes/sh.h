/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/09 19:55:32 by pbourrie          #+#    #+#             */
/*   Updated: 2016/09/10 01:48:51 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SH_H
# define FT_SH_H

# include <term.h>
# include <termios.h>
# include <termcap.h>
# include <sys/ioctl.h>

# include <dirent.h>

# include <signal.h>
# include <sys/mount.h>
# include <fcntl.h>

# include "libft.h"
# include "sh_data.h"

/*
**   INI_ENV
*/
t_env		*init_env(char **environ);
void		init_env_var(t_env *e, char **environ);
void		init_shlvl(t_env *e);
void		init_pwd(t_env *e);
void		refresh_nb_col(t_env *e);

/*
**   SCRIPT
*/
int			execute_script(t_env *e, char *path, char error);
int			execute_script_open(char *path, int *fd, char error);
void		load_rc(t_env *e);

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
**   BUILTIN
*/
int			process_builtin(t_env *e);
int			process_builtin_2(t_env *e);

/*
**   BUILTIN_CD
*/
void		builtin_cd(t_env *e);
int			builtin_cd_get_opt(t_env *e, char *opt_p);
void		builtin_cd_setenv(t_env *e, char opt_p, char *new_pwd);
void		builtin_cd_error(t_env *e, char *path, char opt);

/*
**   BUILTIN_CD_TOOLS
*/
void		builtin_cd_clean_path(char *new_pwd, int i);
void		builtin_cd_parse_dotdot(char *new_pwd, int *i, int last, int len);

/*
**   BUILTIN_ECHO
*/
void		builtin_echo(t_env *e);

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
**   BUILTIN_HASH
*/
void		builtin_hash(t_env *e);
t_hash_stat	*builtin_hash_load(t_env *e);
void		builtin_hash_load2(t_env *e, t_hash_stat *stats, t_hash_b *tmp);
int			builtin_hash_get_opt(t_env *e, char *opt_r, char *opt_s);

/*
**   BUILTIN_HASH_PRINT
*/
void		builtin_hash_print(t_env *e, char opt_s);
void		builtin_hash_print_stats(t_env *e, t_hash_stat *stats);
void		builtin_hash_print_colstats(t_env *e, t_hash_stat *stats);

/*
**   BUILTIN_ALIAS
*/
void		builtin_alias(t_env *e);
void		builtin_alias_add_check(t_env *e, char *str);
void		builtin_alias_add(t_env *e, char *key, char *val);
void		builtin_alias_print(t_env *e, char *key);

/*
**   BUILTIN_UNALIAS
*/
void		builtin_unalias(t_env *e);
void		builtin_unalias_remove(t_env *e, char *name);

/*
**   GET_BIN_PATH
*/
void		set_bin_path(t_env *e);
char		*get_cmd_path(t_env *e, char *cmd);
void		load_builtin_list(t_env *e);

/*
**   HASH_TABLE
*/
int			hash1(char *name, int size);
char		*hash_find(t_env *e, char *key);
char		*hash_add_cmd(t_env *e, char *cmd);
char		*hash_add(t_env *e, char *key, char *val);
void		hash_autofill(t_env *e);

/*
**   HASH_TABLE_TOOLS
*/
void		hash_table_resize(t_env *e);
void		hash_table_rebuilt(t_env *e, t_hash_b **old_table, int old_total);

/*
**   SORT
*/
void		myqsort(char **stab, int beg, int end);

/*
**   HOME
*/
void		set_home_path(t_env *e);

/*
**   GET_CMD
*/
void		get_cmd(t_env *e);
t_parse		get_cmd_is_ended(t_env *e);
int			get_cmd_get_end(t_env *e, t_parse *l, char **line_start, int type);
int			get_cmd_end(t_env *e, char type, int ret);
int			get_input_line(t_env *e, int eof_exit);

/*
**   EDITOR
*/
int			get_term_line_input(t_env *e, int eof_exit);
int			process_all_key(t_env *e, int ret, char *buf, int eof_exit);
void		get_input_chars(t_env *e, char *buf);
void		get_input_char(t_env *e, char c);

/*
**   EDITOR CONTROL KEY
*/
int			process_control_key(t_env *e, int ret, char *buf, int eof_exit);
int			process_break_key(t_env *e, int ret, char *buf);
int			process_completion_key(t_env *e, int ret, char *buf);

/*
**   EDITOR CURSOR KEY
*/
int			process_cursor_key(t_env *e, int ret, char *buf);
int			process_cursor2_key(t_env *e, int ret, char *buf);
int			process_home_end_key(t_env *e, int ret, char *buf);
int			process_prev_word_key(t_env *e, int ret, char *buf);
int			process_next_word_key(t_env *e, int ret, char *buf);

/*
**   EDITOR EDITION KEY
*/
int			process_edition_key(t_env *e, int ret, char *buf);
int			process_histo_up_key(t_env *e, char *buf);
int			process_histo_down_key(t_env *e, char *buf);

/*
**   EDITOR EDITION
*/
void		delete_input_nchar(t_env *e, int n);
void		backdelete_input_char(t_env *e);
void		cut_input_line(t_env *e);
void		paste_input_line(t_env *e);
void		switch_to_histo(t_env *e);

/*
**   EDITOR_LINE
*/
void		refresh_eol(t_env *e);
void		put_line_char(t_env *e, int cur);
void		put_line(t_env *e, int start);

/*
**   EDITOR CURSOR
*/
int			move_cursor_right(t_env *e);
int			move_cursor_left(t_env *e);
void		move_cursor_left_char_parse(t_env *e, int *nb);
int			get_cur_pos(t_env *e, int cur);
void		get_cur_pos_loop(t_env *e, int *i, int *pos);

/*
**   EDITOR TOOLS
*/
void		realloc_input_line(t_env *e);
int			is_end_of_line(t_env *e, int cur);
int			ft_outc(int c);
void		close_line_edition(t_env *e);

/*
**   EDITOR_COMPLETION
*/
void		editor_completion(t_env *e);
void		editor_completion_complete(t_env *e);
void		editor_completion_complete_end(t_env *e);
void		editor_completion_complete_end_link(t_env *e);
char		*escape_simple_quotes(char *str);

/*
**   EDITOR_COMPLETION_PRINT
*/
void		editor_completion_print(t_env *e);
int			editor_completion_print_ask(t_env *e);
void		editor_completion_print_col(t_env *e);
void		editor_completion_print_one(t_env *e, int id);

/*
**   EDITOR_SEARCH
*/
char		*editor_search(t_env *e);
void		editor_search_refresh(t_env *e, char *search, int num);
int			editor_search_key(char *buf, char **search, int *num);
void		editor_search_exit(t_env *e, char *buf, char *search, char *prom);

/*
**   EDITOR_SEARCH_PRINT
*/
void		editor_search_print(t_env *e, char *line, char *search, char *prom);
void		editor_search_print_prompt(t_env *e, char *search, char *prompt);
void		editor_search_position_cursor(t_env *e, char *search);

/*
**   COMPLETION
*/
void		completion_update(t_env *e);
void		completion_addtoposs(t_env *e, char *str);
void		completion_check_mutual(t_env *e);
void		completion_free(t_env *e);

/*
**   COMPLETION_GET_POSS
*/
void		completion_get_poss(t_env *e);
void		completion_get_var_poss(t_env *e, int len);
void		completion_get_cmd_poss(t_env *e, int len);
void		completion_get_alias_poss(t_env *e, int len);

/*
**   COMPLETION_GET_FILE_POSS
*/
void		completion_get_file_poss(t_env *e, char *path);
void		completion_add_dirent(t_env *e, t_dirent *dir_ent, char *path);

/*
**	 LEXER
*/
void		lexer_init(t_env *e, t_parse *lex, int end);
void		lexer(t_env *e, t_parse *lex, int end);
void		lexer_add_arg(t_parse *l);
void		lexer_add_cmd(t_parse *l, int separ);
int			lexer_add_to_buf(t_env *e, t_parse *l);

/*
**   LEXER ELEMENT
*/
int			lexer_quotes(t_env *e, t_parse *l);
int			lexer_bquotes_pipes(t_env *e, t_parse *l);
int			lexer_operator_delim(t_env *e, t_parse *l);
int			lexer_exp_redir(t_env *e, t_parse *l);
int			lexer_space_escape(t_env *e, t_parse *l);

/*
**   HISTORY
*/
void		history_init(t_env *e);
void		history_load(t_env *e);
void		history_save_ent(t_env *e, char *ent);
void		history_add_to_mem(t_env *e, char *line);

/*
**   HISTORY_FIND
*/
char		*history_find(t_env *e, char *str, int num);

/*
**   PARSE_CMD
*/
void		parse_cmd(t_env *e);
int			parse_cmd_check_eol(t_env *e, t_parse *p);
void		parse_cmd_loop_end(t_env *e, t_parse *p);
int			parse_cmd_is_end(t_parse *p);

/*
**   PARSE_CMD_INIT
*/
void		parse_init(t_env *e, t_parse *p);
void		parse_init_cmd(t_env *e, t_parse *p);

/*
**   PARSE_CMD_ELEMENT_P1
*/
int			parse_cmd_quotes(t_env *e, t_parse *p);
int			parse_cmd_operator_parenthesis(t_env *e, t_parse *p);
int			parse_cmd_operator_ampersand(t_env *e, t_parse *p);
int			parse_cmd_pipe_comma(t_env *e, t_parse *p);
int			parse_cmd_expansion(t_env *e, t_parse *p);

/*
**   PARSE_CMD_ELEMENT_P2
*/
int			parse_cmd_redirection(t_env *e, t_parse *p);
int			parse_cmd_space_backslash(t_env *e, t_parse *p);
int			parse_cmd_add_to_buf(t_env *e, t_parse *p);
void		parse_cmd_reset_quotes(t_env *e, t_parse *p);
int			parse_operators(t_env *e, t_parse *p, int separ, char doub);

/*
**   PARSE_CMD_ADD_ELEMENT
*/
void		parse_add_cmd(t_env *e, t_parse *p, char sep);
int			parse_add_arg(t_env *e, t_parse *p);
void		parse_add_arg_malloc(t_env *e, t_parse *p);
int			parse_add_arg_redir_alias(t_env *e, t_parse *p);
void		parse_add_cmd_sep(t_env *e, t_parse *p, char sep);

/*
**   PARSE_CMD_ADD_REDIRECTION
*/
int			parse_add_redirec(t_env *e, t_parse *p);
void		parse_add_redirec_p2(t_parse *p);
void		parse_get_redirec_type(t_env *e, t_parse *p);
void		new_redirec(t_env *e, char *file, int type, int fd);

/*
**   PARSE_CMD_TOOLS
*/
int			is_aspace(char c);
void		parse_cmd_cleanline(t_env *e);
void		realloc_parse_buffer(t_parse *p, int add);
char		*dup_arg(char *buf);
void		parse_cmd_put_error(t_parse *p);

/*
**   PARSE_CMD_EXPANSION
*/
void		parse_var_expansion(t_env *e, t_parse *p);
void		parse_var_expansion2(t_env *e, t_parse *p, char *arg, char *new);
void		parse_tilde_expansion(t_env *e, t_parse *p);

/*
**   PARSE_CMD_SUBSTITUTION
*/
void		parse_cmd_substitution(t_env *e, t_parse *p);
char		*parse_cmd_substitution_fork(t_env *e, int *fd, char *cmd);
char		*parse_cmd_substitution_get_output(t_env *e, int *fd, pid_t pid);
void		parse_cmd_substi_line(t_env *e, t_parse *p, char *out, int start);

/*
**   PARSE_CMD_SUBSTITUTION_PARSE_LINE
*/
int			parse_cmd_substi_parse_line(t_env *e, t_parse *p, char *cmd);
void		parse_cmd_substi_parse_line_quotes(t_env *e, t_parse *p);

/*
**   PARSE_CMD_ALIAS
*/
int			parse_cmd_alias(t_env *e, t_parse *p);
void		parse_cmd_alias_addtoline(t_env *e, t_parse *p, char *cmd);
void		parse_cmd_alias_rec(t_env *e, t_parse *p, char **cmd);

/*
**   PARSE_CMD_SUBCMD
*/
void		parse_cmd_subcmd(t_env *e, t_parse *p);
int			parse_cmd_subcmd_parse_line(t_env *e, t_parse *p);
void		parse_cmd_subcmd_parse_line_quotes(t_env *e, t_parse *p);

/*
**   EXECUTE
*/
void		process_cmd(t_env *e);
void		process_bin(t_env *e, char **env, char dofork);
void		process_fork(t_env *e, char *cmd_path, char **env, char dofork);
void		process_set_child_attr(t_env *e, pid_t pid);
void		process_init_child(t_env *e);

/*
**   EXECUTE_SUB_AND_PIPE
*/
void		process_fork_subcmd(t_env *e, char dofork);
void		process_piped_cmd(t_env *e);
void		process_piped_cmd_child(t_env *e);

/*
**   WAIT
*/
void		process_wait(t_env *e, pid_t pid, int job);
void		process_wait_status(t_env *e, int status, pid_t pid, int job);
void		process_wait_sigstop(t_env *e, int status, pid_t pid, int job);
void		process_wait_error(t_env *e, int ret, int isjob, pid_t pid);

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
int			redirec_open_all(t_env *e);
int			redirec_open_p1(t_env *e, t_redir *redir);
int			redirec_open_p2(t_env *e, t_redir *redir);
void		redirec_assign(t_env *e);
void		redirec_close(t_env *e, int cid);

/*
**   REDIRECTIONS_TOOLS
*/
int			redirec_open_files(t_redir *redir);
int			redirec_open_dupfd(t_redir *redir);
void		redirec_assign_dupfd(t_redir *redir);
int			getcurstdfd(t_env *e, int fd);
void		open_file_error(char *path, int type);

/*
**   PIPE
*/
int			pipe_new(t_env *e, t_redir *redir);
void		pipe_assign(t_env *e);
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
**   TERM_TOOLS
*/
void		term_set_tcpgid(t_env *e, pid_t pgid);

/*
**   TERM LOAD INFO
*/
void		term_load_info(t_env *e);
void		term_load_key_default(t_env *e);
void		term_load_key_default2(t_env *e);
void		term_load_key(t_env *e);
void		term_load_key2(t_env *e);

/*
**   JOBS
*/
void		jobs_continue(t_env *e, int fg);
int			jobs_continue_getjob(t_env *e, int fg, int id);
void		jobs_remove(t_env *e, pid_t pgid);
void		jobs_remove_notif(t_env *e, t_job *job);
void		jobs_list(t_env *e);

/*
**   JOBS_TOOLS
*/
void		jobs_update_status(t_env *e);
void		jobs_put_job_status(t_env *e, pid_t pgid, char nl, char *status);
t_job		*jobs_find(t_env *e, pid_t pgid, int id);
void		jobs_add(t_env *e, pid_t pgid, int bg);
int			jobs_get_new_id(t_env *e, pid_t pgid);

/*
**   PROMPT
*/
void		print_prompt(t_env *e);
void		gen_prompt(t_env *e, char *str);
char		*ft_get_dir_up(char *path, int level);

/*
**   FREE_ENV
*/
void		free_env(t_env *e);
void		free_env_var(t_env *e);

/*
**   FREE_SUB_ENV
*/
void		free_history(t_env *e);
void		kill_jobs(t_env *e);
void		free_path_and_env(t_env *e);
void		free_hash_table(t_env *e);
void		free_alias(t_env *e);

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
void		put_cmd_opt_error(char *cmd, char opt, int fd, char *usage);

/*
**   SIGNAL
*/
void		catch_signal(void);
void		sig_handler(t_env *e, int signum);
void		sig_mediator(int signum);
void		signal_default(void);

#endif
