/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoodale <egoodale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 19:03:21 by egoodale          #+#    #+#             */
/*   Updated: 2018/05/19 19:13:27 by egoodale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#   ifndef FT_LS_H
#   define FT_LS_H

#include "macrosoft.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/xattr.h>
#include <sys/stat.h>
#include <unistd.h>

#define PATH_MAX 1024

typedef struct stat		t_stat;
typedef struct dirent	t_dirent;
typedef struct passwd	t_passwd;
typedef struct group	t_group;

typedef struct	s_coord
{
	int			x;
	int			y;
}				t_coord;

typedef enum	e_sortkey
{
	by_name = (1 << 0),
	by_time = (1 << 1),
	reverse = (1 << 2)
}				t_sortkey;

typedef enum    e_flag
{
    l = (1 << 0),  	//f_longform = 1
    R = (1 << 1),	//f_recursive = 1
    a = (1 << 2),	//fts_options |= FTS_SEEDOT turn on see_dot FTS OPTIONS
    r = (1 << 3), 	//f_reversesort = 1
    t = (1 << 4),	//sort_key = BY_TIME
	at = (1 << 5)  	//getxattrs
}               t_flag;

typedef struct		s_entry
{
	char			*name
	char			full_path[PATH_MAX];
	dev_t			st_dev;
	ino_t			st_ino;
	mode_t			st_mode;
	nlink_t			st_nlink;
	uid_t			st_uid;
	gid_t			st_gid;
	dev_t			st_rdev;
	off_t			st_size;
	blksize_t		st_blksize;
	blkcnt_t		st_blocks;
	long			ntime;
	struct s_entry	*next;
	t_list			children;
}					t_entry;

t_entry			*init_entry(t_stat *e_stat, char path[PATH_MAX]);
char			check_args(char **arg_list, char **path, int ac);
int				throw_err(char *msg);
#   endif