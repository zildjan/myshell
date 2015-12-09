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
	char	*buf;
	int		ib;
	int		a_id;
	char	bslash;
}				t_parse;

typedef struct	s_cmd
{
	char		**arg;
	char		*quo;
	int			pid;
	int			pipe[2];
	char		*in;
	char		*out;
	char		out_appending;
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
