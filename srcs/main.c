/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 20:26:03 by srouhe            #+#    #+#             */
/*   Updated: 2019/12/18 20:39:28 by srouhe           ###   ########.fr       */
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
** 		Init struct for ls command information
*/

static t_ls		*init(char **av)
{
	t_ls		*ls;

	if (!(ls = (t_ls *)malloc(sizeof(t_ls))))
		exit_program(2);
	ls->flags = parse_options(av);
	ls->args = NULL;
	ls->ac = 0;
	ls->width = 0;
	ls->total = 0;
	ls->objs = 0;
	ls->cols = 0;
	ls->w_uid = 0;
	ls->w_gid = 0;
	ls->w_size = 0;
	ls->w_links = 0;
	ls->dirs = 0; /* maybe not needed */
	ls->index = 0;
	return (ls);
}

int				main(int ac, char **av)
{
	t_ls	*ls;
	int		i;

	i = 0;
	ls = init(av);
	parse_arguments(av, &ls);
	sort_arguments(&ls);
	while (ls->args[i])
	{
		ls->dirname = ls->args[i];
		ft_ls(&ls);
		i++;
		if (i < ls->ac)
			ft_putchar('\n');
	}
	// while (av[i] && av[i][0] == '-')
	// 	i++;
	// if (av[i])
	// {
	// 	ls->dirs = av[i + 1] ? 1 : 0;
	// 	while (av[i])
	// 	{
	// 		ls->dirname = ft_strdup(av[i]);
	// 		ft_ls(&ls);
	// 		ft_strdel(&ls->dirname);
	// 		i++;
	// 	}
	// }
	// else
	// {
	// 	ls->dirname = ft_strdup(".");
	// 	ft_ls(&ls);
	// 	ft_strdel(&ls->dirname);
	// }
	free(ls);
	if (ac > 6)
		while(1);
	return (0);
}
