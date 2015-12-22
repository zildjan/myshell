/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_data.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/09 19:55:32 by pbourrie          #+#    #+#             */
/*   Updated: 2015/12/17 21:50:42 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SH_DATA_H
# define FT_SH_DATA_H

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

# define SEP_PIPE 1
# define SEP_AND 2
# define SEP_OR 3

typedef struct	s_job
{
	char			*name;
	int				id;
	int				pid;
	int				pgid;
	struct s_job	*next;
}				t_job;

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

typedef struct	s_parse
{
	char	quo;
	char	escape;
	char	*buf;
	int		i;
	int		ib;
	int		a_id;
	int		error;
	int		separ;
	int		line_len;
	int		redirec;
	int		redirec_fd;
	char	*last_arg;
}				t_parse;

typedef struct	s_cmd
{
	char		**arg;
	char		condi;
	int			pid;
	int			pgid;
	int			fd_in;
	int			fd_out;
	int			fd_err;
	int			pipe[2];
	char		piped;
	t_redir		*redir;
	t_hdoc		*hdoc;
	int			hdoc_pipe[2];
	int			status;
}				t_cmd;

typedef struct	s_env
{
	char	*line;
	t_cmd	*cmd;
	char	**carg;
	int		cid;
	int		nb_cmd;
	int		wait_cid;
	int		cmd_pgid;
	char	**var;
	int		tab_size;
	char	**path;
	char	*home;
	char	*home_dir;
	char	*pwd;
	int		status;
	t_job	*job;
	t_job	*jobs_lst;
}				t_env;

#endif
