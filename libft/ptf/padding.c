/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padding.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 18:10:26 by srouhe            #+#    #+#             */
/*   Updated: 2019/12/05 18:02:09 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		padding_leading(t_ptf **p)
{
	int		i;
	int		j;
	char	*r;

	j = 0;
	i = (*p)->width - (*p)->tmplen;
	if (i > 0)
	{
		r = ft_memalloc(sizeof(char) * (*p)->width);
		r = ft_memset(r, (*p)->padc, i);
		while (i < (int)(*p)->width)
			r[i++] = (*p)->tmp[j++];
		(*p)->tmplen = (*p)->width;
		free((*p)->tmp);
		(*p)->tmp = ft_memdup(r, (*p)->width);
		free(r);
	}
}

void		padding_trailing(t_ptf **p)
{
	int		i;
	int		j;
	char	*r;

	j = 0;
	i = (*p)->width - (*p)->tmplen;
	if (i > 0)
	{
		r = ft_memalloc(sizeof(char) * (*p)->width);
		r = ft_memset(r, (*p)->padc, (*p)->width);
		while (j < (int)(*p)->tmplen)
		{
			r[j] = (*p)->tmp[j];
			j++;
		}
		(*p)->tmplen = (*p)->width;
		free((*p)->tmp);
		(*p)->tmp = ft_memdup(r, (*p)->width);
		free(r);
	}
}
