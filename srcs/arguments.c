/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 20:33:12 by srouhe            #+#    #+#             */
/*   Updated: 2019/12/19 12:15:36 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** 		Parse options
*/

short		parse_options(char **av)
{
	int		i;
	int		j;
	short	flags;

	i = 1;
	j = 0;
	flags = 0;
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
** 		Parse arguments
*/

void		parse_arguments(char **av, int ac, t_obj **head, t_ls **ls)
{
	int		i;
	t_obj	*obj;

	i = 1;
	while (av[i] && av[i][0] == '-')
		i++;
	(*ls)->ac = ac - i;
	if (!(*ls)->ac)
	{
		obj = new_mini_obj(ft_strdup("."));
		addlst(head, obj);
	}
	while (av[i])
	{
		obj = new_mini_obj(ft_strdup(av[i]));
		if (obj)
			addlst(head, obj);
		else
			(*ls)->ac--;
		i++;
	}
}
