/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 20:33:12 by srouhe            #+#    #+#             */
/*   Updated: 2019/12/18 20:49:59 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
**		Sort argv folders passed as arguments
*/

void		sort_arguments(t_ls **ls)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	while (j < (*ls)->ac)
	{
		i = 0;
		while (i < (*ls)->ac - 1)
		{
			if (ft_strcmp((*ls)->args[i], (*ls)->args[i + 1]) > 0)
			{
				tmp = (*ls)->args[i];
				(*ls)->args[i] = (*ls)->args[i + 1];
				(*ls)->args[i + 1] = tmp;
			}
			i++;
		}
		j++;
	}
}

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

void		parse_arguments(char **av, t_ls **ls)
{
	int	i;
	int j;
	int k;

	i = 1;
	j = 0;
	k = 0;
	while (av[i] && av[i][0] == '-')
		i++;
	while (av[i])
	{
		i++;
		j++;	
	}
	i -= j;
	(*ls)->ac = j;
	if (!j)
	{
		if (!((*ls)->args = (char **)malloc(sizeof(char *) * 2)))
			exit_program(2);
		(*ls)->args[0] = ft_strdup(".");
		(*ls)->args[1] = NULL;
		return ;
	}
	if (!((*ls)->args = (char **)malloc(sizeof(char *) * (j + 1))))
		exit_program(2);
	while (av[i])
	{
		(*ls)->args[k] = ft_strdup(av[i]);
		i++;
		k++;	
	}
	(*ls)->args[k] = NULL;
}