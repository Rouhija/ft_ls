/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 16:47:30 by srouhe            #+#    #+#             */
/*   Updated: 2019/12/17 13:03:15 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** 		Get right padding based on current shell size
*/

static int		get_padding(t_ls **ls, int ws_col)
{
	struct winsize	w;
	int				width;

	width = (*ls)->width;
	ioctl(1, TIOCGSIZE, &w);
	if (width < 16 && (*ls)->objs * 16 < ws_col)
		return (16);
	// else if ((*ls)->width < 24)
	// 	return (24);
	else
		return(width + 6);	
}

/*
**		Print ls -l format
*/

void			print_obj_long(t_obj *obj, t_ls **ls)
{
	ft_printf("%-10s %d %-7s %.4s %6zu %.12s %s\n", 
		obj->rights,
		obj->st_nlink, // check length!!
		obj->st_uid,
		&obj->dt[16],
		obj->st_size,
		obj->dt,
		obj->name
	);
}

/*
**		Print with columnar format
*/

void			print_obj_short(t_obj *obj, t_ls **ls)
{
	struct winsize	w;
	static int		i;
	// int				cols;
	// int				rows;
	int				padding;

	ioctl(1, TIOCGSIZE, &w);
	// padding = get_padding(ls, w.ws_col);
	// cols = w.ws_col / padding;
	// rows = cols / (*ls)->objs;
	i++;
	if (obj->rights[0] == 'd')
		ft_putstr("\033[01;32m");
	// ft_printf("%d", padding);
	ft_printf("%-*s", 16, obj->name); // HERE IS THE PROBLEM!! CHECK COLUMNAR FORMAT
	if (obj->rights[0] == 'd')
		ft_putstr("\033[0m");
	// if (cols == i)
	// {
	// 	ft_putchar('\n');
	// 	i = 0;
	// }
}


/*
** 		Delete and free object
*/

void		object_del(t_obj *obj, t_ls **ls)
{
	if (obj)
	{
		free(obj->path);
		free(obj->name);
		free(obj->rights);
		free(obj->st_uid);
		free(obj->dt);
		free(obj);
	}
	if (ls && *ls)
	{
		(*ls)->width = 0;
		(*ls)->total = 0;
		(*ls)->objs = 0;		
	}
}

/*
** 		Create new object 
*/

t_obj			*new_obj(char *dirname, char *filename)
{
	t_obj			*obj;
	struct stat 	attr;

	if (!(obj = (t_obj *)malloc(sizeof(t_obj))))
		exit_program(2);
	obj->st_mode = attr.st_mode;
	obj->path = pathjoin(dirname, filename);
	stat(obj->path, &attr);
	obj->name = ft_strdup(filename);
	obj->rights = permissions((int)attr.st_mode);
	obj->st_nlink = attr.st_nlink;
	obj->st_uid = ft_strdup(getpwuid(attr.st_uid)->pw_name);
	obj->st_size = attr.st_size;
	obj->dt = ft_strdup(&(ctime(&attr.st_mtime)[4]));
	obj->st_time = attr.st_mtime;
	obj->st_blocks = attr.st_blocks;
	obj->next = NULL;
	return (obj);
}