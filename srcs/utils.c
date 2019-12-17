/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 15:47:10 by srouhe            #+#    #+#             */
/*   Updated: 2019/12/17 11:16:14 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
**		Join directory and file into a path
*/

char			*pathjoin(char *dirname, char *filename)
{
	char	*path;

	if (dirname[ft_strlen(dirname) - 1] == '/')
		path = ft_strjoin(dirname, filename);
	else
		path = ft_strjoin(ft_strjoin(dirname, "/"), filename);
	return (path);
}

/*
**		Stringify object permissions
*/

char			*permissions(int st_mode)
{
	char	*rights;

	rights = (char *)malloc(sizeof(char) * 11);
	rights[0] = S_ISDIR(st_mode) ? 'd' : '-';
	// rights[0] = S_ISLNK(st_mode) ? 'l' : '-';
	rights[1] = st_mode & S_IRUSR ? 'r' : '-';
	rights[2] = st_mode & S_IWUSR ? 'w' : '-';
	rights[3] = st_mode & S_IXUSR ? 'x' : '-';
	rights[4] = st_mode & S_IRGRP ? 'r' : '-';
	rights[5] = st_mode & S_IWGRP ? 'w' : '-';
	rights[6] = st_mode & S_IXGRP ? 'x' : '-';
	rights[7] = st_mode & S_IROTH ? 'r' : '-';
	rights[8] = st_mode & S_IWOTH ? 'w' : '-';
	rights[9] = st_mode & S_IXOTH ? 'x' : '-';
	rights[10] = '\0';
	return (rights);
}
