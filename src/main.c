/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/09 12:18:49 by pbourrie          #+#    #+#             */
/*   Updated: 2016/05/27 23:53:07 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		main(int argc, char **argv, char **environ)
{
	t_env	*e;

	e = init_env(environ);
	sig_handler(e, 0);
	catch_signal();
	if (argc > 1)
		return (execute_script(e, argv[1]));
	load_rc(e);
	while (1)
	{
		if (isatty(0))
		{
			gen_prompt(e, NULL);
			print_prompt(e);
		}
		get_cmd(e);
	}
	return (0);
}

void	load_rc(t_env *e)
{
	char	*path;

	path = ft_strdup(e->home);
	path = ft_strdupcat(path, "/.21shrc");
	execute_script(e, path);
	free(path);
}

int		execute_script(t_env *e, char *path)
{
	int		fd;
	int		type;
	int		ret;

	fd = 0;
	ret = 126;
	type = ft_get_file_type(path);
	if (type == -1)
		ret = 127;
	if (type != 'd')
		fd = open(path, O_RDONLY);
	if (fd <= 0)
	{
		if (type == -1)
			put_error(ERRNOENT, NULL, path, 2);
		else if (type == 'd')
			put_error(ERRISDIR, NULL, path, 2);
		else if (access(path, R_OK))
			put_error(ERRACCES, NULL, path, 2);
		else
			put_error(100, NULL, path, 2);
		return (ret);
	}

//		ft_printf("fd=%d\n", fd);

	e->line = NULL;
	while (get_next_line(fd, &e->line) > 0)
	{
		parse_cmd(e);
		free(e->line);
		e->line = NULL;
	}
	if (e->line)
		free(e->line);
	close(fd);
	return (0);
}
