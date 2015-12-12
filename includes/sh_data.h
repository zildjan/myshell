/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_data.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/09 19:55:32 by pbourrie          #+#    #+#             */
/*   Updated: 2015/11/13 22:30:25 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SH_DATA_H
# define FT_SH_DATA_H

# define ERRACCES 1
# define ERRNOENT 2
# define ERRNOTDIR 3
# define ERRNOCMD 4
# define ERREXEFORM 5

# define NONE 0
# define SIMP 1
# define DOUB 2

# define NONE 0
# define R_IN 1
# define R_OUT 2
# define R_OUTA 3
# define R_HDOC 4
# define R_PIPE 5
# define R_PIPED 6

# define EP_NULL_CMD 1
# define EP_AMB_OUT 2
# define EP_AMB_IN 3
# define EP_MISS_REDIREC 4

typedef struct	s_job
{
	char			*name;
	int				id;
	int				pgid;
	struct s_job	*next;
}				t_job;

typedef struct	s_parse
{
	char	quo;
	char	escape;
	char	*buf;
	int		i;
	int		ib;
	int		a_id;
	int		error;
	int		line_len;
	int		redirec;
}				t_parse;

typedef struct	s_cmd
{
	char		**arg;
	char		*quo;
	int			pid;
	int			pipe[2];
	char		*in;
	char		*out;
	int			in_t;
	int			out_t;
}				t_cmd;

typedef struct	s_env
{
	char	*line;
	t_cmd	*cmd;
	char	**carg;
	int		cid;
	int		nb_cmd;
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
