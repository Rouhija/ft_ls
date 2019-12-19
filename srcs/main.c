/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 20:26:03 by srouhe            #+#    #+#             */
/*   Updated: 2019/12/19 13:11:52 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** 		0 if OK,
** 		1 if minor problems (e.g., cannot access subdirectory),
** 		2 if serious trouble (e.g., cannot access command-line argument).
*/

void			exit_program(int reason)
{
	reason == 0 ? ft_putendl("usage: ./ft_ls [-Ralrt] [file ...]") : PASS;
	reason == 1 ? ft_putendl("error") : PASS;
	reason == 2 ? ft_putendl("malloc fail.") : PASS;
	exit(reason);
}

/*
**		Handle invalid paths
*/

void			errors(char *path, int code)
{
	if (code == 1)
	{
		ft_putstr("./ft_ls: ");
		ft_putstr(path);
		ft_putendl(": No such file or directory");
	}
	else if (code == 2)
	{
		ft_putstr("./ft_ls: ");
		ft_putstr(path);
		ft_putendl(": Permission denied");
	}
}

/*
** 		Init struct for ls command information
*/

static t_ls		*init(char **av)
{
	t_ls		*ls;

	if (!(ls = (t_ls *)malloc(sizeof(t_ls))))
		exit_program(2);
	ls->flags = parse_options(av);
	ls->ac = 0;
	ls->width = 0;
	ls->total = 0;
	ls->objs = 0;
	ls->cols = 0;
	ls->w_uid = 0;
	ls->w_gid = 0;
	ls->w_size = 0;
	ls->w_links = 0;
	ls->index = 0;
	return (ls);
}

static	void	iterate_args(t_ls **ls, t_obj *args)
{
	t_obj	*tmp;
	int		i;

	i = 0;
	while (args)
	{
		if (S_ISDIR(args->st_mode))
		{
			(*ls)->dirname = args->path;
			ft_ls(ls);
		}
		else
			ft_putendl(args->path);
		tmp = args;
		args = args->next;
		minidel(tmp);
		i++;
		if (i < (*ls)->ac)
			ft_putchar('\n');
	}
}

int				main(int ac, char **av)
{
	t_ls	*ls;
	t_obj	*args;

	ls = init(av);
	args = NULL;
	parse_arguments(av, ac, &args, &ls);
	merge_sort(&args, &ls);
	iterate_args(&ls, args);
	free(ls);
	return (0);
}
