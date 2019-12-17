/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 20:26:03 by srouhe            #+#    #+#             */
/*   Updated: 2019/12/17 19:20:57 by srouhe           ###   ########.fr       */
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
	reason == 1 ? ft_putendl("opendir fail") : PASS;
	reason == 2 ? ft_putendl("malloc fail.") : PASS;
	exit(reason);
}

/*
** 		Parse options to struct and move pointer of argv
*/

static short	parse_options(char **av)
{
	int		i;
	int		j;
	short	flags;

	i = 1;
	j = 0;
	while (av[i] && av[i][0] == '-')
	{
		j = 0;
		while (av[i][j])
		{
			j++;
			ft_strchr(OPTIONS, av[i][j]) ? PASS : exit_program(0);
			flags |= av[i][j] == 'l' ? LLIST : NUL;
			flags |= av[i][j] == 'R' ? RECURSE : NUL;
			flags |= av[i][j] == 'a' ? HIDDEN : NUL;
			flags |= av[i][j] == 'r' ? RSORT : NUL;
			flags |= av[i][j] == 't' ? TSORT : NUL;
		}
		i++;
	}
	return (flags);
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
	ls->width = 0;
	ls->total = 0;
	ls->objs = 0;
	ls->cols = 0;
	ls->w_uid = 0;
	ls->w_gid = 0;
	ls->w_size = 0;
	ls->w_links = 0;
	ls->dirs = 0;
	return (ls);
}

int				main(int ac, char **av)
{
	t_ls	*ls;
	int		i;

	i = 1;
	ls = init(av);
	while (av[i] && av[i][0] == '-')
		i++;
	if (av[i])
	{
		ls->dirs = av[i + 1] ? 1 : 0;
		while (av[i])
		{
			ls->dirname = ft_strdup(av[i]);
			ft_ls(&ls);
			ft_strdel(&ls->dirname);
			i++;
		}
	}
	else
	{
		ls->dirname = ft_strdup(".");
		ft_ls(&ls);
		ft_strdel(&ls->dirname);
	}
	free(ls);
	if (ac > 4)
		while(1);
	return (0);
}
