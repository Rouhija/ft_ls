/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 20:20:17 by srouhe            #+#    #+#             */
/*   Updated: 2019/12/05 15:35:53 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	hex_prefix(t_ptf **p)
{
	int		i;
	char	*r;

	i = 0;
	(*p)->tmplen += 2;
	r = ft_memalloc(sizeof(char) * (*p)->tmplen);
	r[0] = '0';
	r[1] = 'x';
	while (i < (int)(*p)->tmplen)
	{
		r[i + 2] = (*p)->tmp[i];
		i++;
	}
	free((*p)->tmp);
	(*p)->tmp = ft_memdup(r, (*p)->tmplen);
	free(r);
}
