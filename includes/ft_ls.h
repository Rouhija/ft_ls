/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 16:58:46 by srouhe            #+#    #+#             */
/*   Updated: 2019/12/19 11:18:35 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

/*
** -------- HEADERS --------
*/

# include "libft.h"
# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/xattr.h>
# include <stdio.h>
# include <string.h>
# include <pwd.h>
# include <grp.h>
// # include <uuid/uuid.h>
# include <time.h>
# include <sys/ioctl.h>

/*
** -------- MACROS --------
*/

# define OPTIONS "Ralrt"
# define SIXMON 15778476
# define LNKBUF 1024

# define LLIST		(1 << 0)
# define RECURSE	(1 << 1)
# define HIDDEN		(1 << 2)
# define RSORT		(1 << 3)
# define TSORT		(1 << 4)
# define NUL		(1 >> 1)

# ifndef TIOCGSIZE
#  define TIOCGSIZE TIOCGWINSZ
# endif

/*
** -------- TYPEDEFS --------
*/

typedef struct		s_obj
{
	mode_t			st_mode;
	char			*path;
	char			*name;
	char			*link;
	char			*rights;
	nlink_t			st_nlink;
	char			*st_uid;
	char			*st_gid;
	off_t			st_size;
	char			*dt;
	time_t			st_time;
	quad_t			st_blocks;
	struct s_obj	*next;
}					t_obj;

typedef struct		s_ls
{
	int				width;
	int				total;
	short			flags;
	int				ac;
	char			*dirname;
	int				objs;
	int				cols;
	int				w_uid;
	int				w_gid;
	int				w_size;
	int				w_links;
	int				index;
}					t_ls;

/*
** -------- FUNCTIONS --------
*/

void				object_del(t_obj **head, t_ls **ls);
void				print_obj_long(t_obj **head, t_ls **ls);
void				print_obj_short(t_obj **head, t_ls **ls);
void				exit_program(int reason);
void				ft_ls(t_ls **ls);
t_obj				*new_obj(char *name, char *path);
char				*pathjoin(char *dirname, char *filename);
char				*permissions(int st_mode);

char				*datestring(char *dt);

void				print_lst(t_list *lst);


void			read_dir(t_ls **ls, t_obj **head, char *dirname);
void			read_dir_a(t_ls **ls, t_obj **head, char *dirname);
void	addlst(t_obj **alst, t_obj *new);
void	objiter(t_obj **lst, t_ls **ls, void (*applyf)(t_obj **, t_ls **));
char    *lst_search(t_obj *lst, int i, int index);
void			recurse_dirs(t_ls **ls, char *dirname);
void			merge_sort(t_obj **headref, t_ls **ls);
void			columns(t_ls **ls);
void			print_obj_cols(t_obj **head, t_ls **ls);
char			*permissions_link(int st_mode);
void			reset_dir(t_ls **ls);
void		parse_arguments(char **av, t_obj **head, t_ls **ls);
short		parse_options(char **av);
t_obj   *sorted_merge_time_rev(t_obj *a, t_obj *b);
t_obj			*new_mini_obj(char *path);
void			minidel(t_obj *obj);

#endif
