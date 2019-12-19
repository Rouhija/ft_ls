/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 15:47:10 by srouhe            #+#    #+#             */
/*   Updated: 2019/12/19 12:43:44 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** 		Reset dir values after iteration
*/

void			reset_dir(t_ls **ls)
{
	(*ls)->width = 0;
	(*ls)->total = 0;
	(*ls)->objs = 0;
	(*ls)->w_uid = 0;
	(*ls)->w_gid = 0;
	(*ls)->w_size = 0;
	(*ls)->w_links = 0;
	(*ls)->index = 0;
}

/*
** 		Check for columnar formatting
*/

void			columns(t_ls **ls)
{
	struct winsize	w;

	ioctl(1, TIOCGSIZE, &w);
	if (((*ls)->width + 7) * (*ls)->objs < w.ws_col)
		(*ls)->cols = 0;
	else
		(*ls)->cols = w.ws_col / ((*ls)->width + 7);
}

/*
**		Join directory and file into a path
*/

char			*pathjoin(char *dirname, char *filename)
{
	char	*path;
	char	*tmp;

	if (dirname[ft_strlen(dirname) - 1] == '/')
		path = ft_strjoin(dirname, filename);
	else
	{
		tmp = ft_strjoin(dirname, "/");
		path = ft_strjoin(tmp, filename);
		free(tmp);
	}
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

/*
**		Stringify link permissions
*/

char			*permissions_link(int st_mode)
{
	char	*rights;

	rights = (char *)malloc(sizeof(char) * 11);
	rights[0] = S_ISLNK(st_mode) ? 'l' : '-';
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
