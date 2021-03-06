/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_data.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/09 19:55:32 by pbourrie          #+#    #+#             */
/*   Updated: 2016/09/10 02:21:51 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SH_DATA_H
# define FT_SH_DATA_H

# define MAX_LEN_LINE 1000000
# define MAX_LEN_ARG 1000
# define MAX_LEN_HDOC 60000

# define ERRACCES 1
# define ERRNOENT 2
# define ERRNOTDIR 3
# define ERRNOCMD 4
# define ERREXEFORM 5
# define ERRISDIR 6

# define NONE 0
# define SIMP 1
# define DOUB 2

# define NONE 0
# define R_IN 1
# define R_OUT 2
# define R_OUTA 3
# define R_HDOC 4
# define R_PIPEIN 5
# define R_PIPEOUT 6
# define R_FDOUT 7
# define R_FDIN 8
# define R_PIPENOT 9

# define EP_NULL_CMD 1
# define EP_AMB_OUT 2
# define EP_AMB_IN 3
# define EP_MISS_REDIREC 4
# define EP_BAD_FD 5
# define EP_SYNTAX 6
# define EP_EOF 7

# define SEP_PIPE 1
# define SEP_AND 2
# define SEP_OR 3

# define EDITION 1
# define PARSING 2
# define EXECUTION 3

typedef struct dirent	t_dirent;

typedef struct	s_job
{
	char			*name;
	int				id;
	pid_t			pgid;
	int				status;
	struct termios	tmodes;
	struct s_job	*next;
}				t_job;

typedef struct	s_hash_b
{
	char			*key;
	char			*val;
	struct s_hash_b	*next;
}				t_hash_b;

typedef struct	s_hash_stat
{
	char			**stab;
	int				col_max;
	int				*col;
	int				i;
	int				i2;
}				t_hash_stat;

typedef struct	s_ti
{
	char			mi;
	char			eo;
	char			xn;
	int				tab_len;
	char			kr[9];
	char			kl[9];
	char			ku[9];
	char			kd[9];
	char			kh[9];
	char			ke[9];
	char			kr_s[9];
	char			kl_s[9];
	char			kh_s[9];
	char			ke_s[9];
	char			ksup[9];
}				t_ti;

typedef struct	s_histo
{
	char			*line;
	struct s_histo	*up;
	struct s_histo	*down;
}				t_histo;

typedef struct	s_parse
{
	char	quo;
	char	quoted;
	char	bquo;
	char	escape;
	int		sub;
	char	is_sub;
	char	*buf;
	int		i;
	int		ib;
	int		a_id;
	int		cid;
	int		error;
	int		separ;
	int		line_len;
	int		buf_len;
	int		redirec;
	int		redirec_fd;
	int		end;
	int		ignore;
	char	doalias;
	int		aliased;
	int		last_i;
}				t_parse;

typedef struct	s_compl
{
	char			**poss;
	char			*start;
	char			*path;
	char			*cstart;
	char			*mutual;
	int				size;
	int				total;
	int				cur;
	int				len_max;
	t_parse			lex;
}				t_compl;

typedef struct	s_alias
{
	char			*key;
	char			*val;
	char			used;
	struct s_alias	*next;
}				t_alias;

typedef struct	s_redir
{
	char			*file;
	int				type;
	int				fd;
	int				fd_to;
	struct s_redir	*next;
}				t_redir;

typedef struct	s_hdoc
{
	char			*content;
	struct s_hdoc	*next;
}				t_hdoc;

typedef struct	s_cmd
{
	char		**arg;
	char		condi;
	char		sub;
	pid_t		pid;
	pid_t		pgid;
	int			fd_in;
	int			fd_out;
	int			fd_err;
	int			pipe[2];
	char		piped;
	t_redir		*redir;
	t_hdoc		*hdoc;
	int			hdoc_pipe[2];
	char		*name;
	int			status;
}				t_cmd;

typedef struct	s_env
{
	pid_t			tc_pgid;
	pid_t			shell_pgid;
	pid_t			last_job;
	int				step;
	char			sub;
	int				fd_in;
	char			**var;
	int				tab_size;
	char			**path;
	t_hash_b		**hash_t;
	int				hash_size;
	int				hash_total;
	t_alias			*alias;
	char			**builtin_list;
	char			*home;
	char			*home_dir;
	char			*pwd;
	int				status;
	char			*prompt;
	int				prompt_len;
	int				ws_col;
	char			*line;
	t_cmd			*cmd;
	char			**carg;
	int				cid;
	int				nb_cmd;
	char			background_cmd;
	t_job			*job;
	t_job			*jobs_lst;
	t_compl			*compl;
	char			*histo_file;
	t_histo			*histo_begin;
	t_histo			*histo;
	t_histo			*histo_cur;
	int				histo_size;
	t_ti			t;
	char			*term_name;
	struct termios	*term;
	struct termios	*term_back;
	int				term_status;
	int				line_size;
	int				line_len;
	char			*line_save;
	int				cur;
	char			*clipboard;
}				t_env;

#endif
