/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_data.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/09 19:55:32 by pbourrie          #+#    #+#             */
/*   Updated: 2015/10/09 21:27:14 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SH_DATA_H
# define FT_SH_DATA_H

# define ERRACCES 1
# define ERRNOENT 2
# define ERRNOTDIR 3
# define ERRNOCMD 4
# define ERREXEFORM 5

typedef struct	s_env
{
	char	*usr_cmd;
	char	**cmd;
	char	**var;
	char	**path;
}				t_env;

#endif
