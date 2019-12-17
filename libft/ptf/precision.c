/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 17:30:33 by srouhe            #+#    #+#             */
/*   Updated: 2019/12/05 15:27:31 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	prec_nbr(t_ptf **p)
{
	int		i;
	int		j;
	char	*r;

	j = 0;
	i = (*p)->prec - (*p)->tmplen;
	if (i > 0)
	{
		r = ft_memalloc(sizeof(char) * (*p)->prec);
		r = ft_memset(r, '0', i);
		while (i < (int)(*p)->prec)
			r[i++] = (*p)->tmp[j++];
		(*p)->tmplen = (*p)->prec;
		free((*p)->tmp);
		(*p)->tmp = ft_memdup(r, (*p)->prec);
		free(r);
	}
}

void	prec_str(t_ptf **p)
{
	int		i;
	char	*r;

	i = 0;
	if ((*p)->tmplen - (*p)->prec > 0)
	{
		r = ft_memalloc(sizeof(char) * (*p)->prec);
		while (i < (int)(*p)->prec)
		{
			r[i] = (*p)->tmp[i];
			i++;
		}
		(*p)->tmplen = (*p)->prec;
		free((*p)->tmp);
		(*p)->tmp = ft_memdup(r, (*p)->prec);
		free(r);
	}
}
