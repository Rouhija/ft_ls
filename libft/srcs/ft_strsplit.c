/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 17:35:12 by srouhe            #+#    #+#             */
/*   Updated: 2019/10/18 17:11:08 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	ft_len(char const *str, char c)
{
	int i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

static int	ft_splits(char const *str, char c)
{
	int	i;
	int flag;
	int words;

	i = 0;
	flag = 0;
	words = 0;
	while (str[i])
	{
		if (str[i] != c && !flag)
		{
			words++;
			flag = 1;
		}
		else if (str[i] == c)
			flag = 0;
		i++;
	}
	return (words);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**range;
	int		i;
	int		j;
	int		flag;

	if (!s || !(range = (char **)malloc(sizeof(char *) * ft_splits(s, c) + 1)))
		return (NULL);
	i = 0;
	j = 0;
	flag = 0;
	while (s[i])
	{
		if (s[i] != c && !flag)
		{
			flag = 1;
			range[j] = ft_memalloc(ft_len(&s[i], c) + 1);
			ft_strncpy(range[j], &s[i], ft_len(&s[i], c));
			j++;
		}
		else if (s[i] == c)
			flag = 0;
		i++;
	}
	range[j] = 0;
	return (range);
}
