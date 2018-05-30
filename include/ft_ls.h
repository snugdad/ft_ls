/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoodale <egoodale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 19:03:21 by egoodale          #+#    #+#             */
/*   Updated: 2018/05/30 13:50:56 by egoodale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#   ifndef FT_LS_H
#   define FT_LS_H

#include "../libftprintf/include/ft_printf.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/xattr.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <sys/ioctl.h>
# include <pwd.h>
# include <grp.h>
# include <uuid/uuid.h>
# include <time.h>
# include <sys/acl.h>

#define ACL_BUFFERMAX 101
#define PATH_MAX 1024
#define MAJOR(x) ((x) & 0xffffff)
#define MINOR(x) ((x >> 24) & 0xf
#define EXP(...) EXP1(EXP1(EXP1(EXP1(__VA_ARGS__))))
#define EXP1(...) EXP2(EXP2(EXP2(EXP2(__VA_ARGS__))))
#define EXP2(...) EXP3(EXP3(EXP3(EXP3(__VA_ARGS__))))
#define EXP3(...) __VA_ARGS__
#define VAR(type_, name, value) EXP(type_ name = value)

typedef struct stat		t_stat;
typedef struct dirent	t_dirent;
typedef struct passwd	t_passwd;
typedef struct group	t_group;
typedef struct ttysize	t_ittys;

enum {ERRNO, USAGE, MALL_ERR};

typedef struct	s_index
{
	int			x;
	int			y;
}				t_index;

typedef enum	e_sortkey
{
	by_time = (1 << 0),
	reverse = (1 << 1)
}				t_sortkey;

typedef enum    e_lsflag
{
    f_lngform = (1 << 0),  	//f_longform = 1
    f_recurse = (1 << 1),	//f_recursive = 1
    f_seedots = (1 << 2),	//fts_options |= FTS_SEEDOT turn on see_dot FTS OPTIONS
    f_revsort = (1 << 3), 	//f_reversesort = 1
    f_timsort = (1 << 4),	//sort_key = BY_TIME
	f_prntatr = (1 << 5),  	//get_attrs
	f_coloset = (1 << 6),	//-G set colors for dir or link/ execute permissions
	f_nmeonly = (1 << 7),	//display directory name only
}               t_lsflag;

typedef enum 	e_report
{
	FAILURE,
	SUCCESS
}				t_report;

typedef struct		s_file
{
	char			*name;
	char			full_path[PATH_MAX];
	dev_t			st_dev;
	ino_t			st_ino;
	mode_t			st_mode;
	nlink_t			st_nlink;
	uid_t			st_uid;
	gid_t			st_gid;
	dev_t			st_rdev;
	off_t			st_size;
	time_t			time;
	long			ntime;
	blksize_t		st_blksize;
	blkcnt_t		st_blocks;
	struct s_file	*next;
	struct s_file	*f_child;

}					t_file;
//MAIN
t_file					*init_file_lst(char **av, int ac, int first);
int						check_args(int ac, char **av, int *flags);

static int				build_full_path(char path[PATH_MAX], char *name, char full_path[PATH_MAX]);
static t_file			*create_new_file(char path[PATH_MAX], char *name, t_stat *stat);
int     				add_new_file(char path[PATH_MAX], char *name, t_file **lst);
t_file					*init_file_lst(char **av, int ac, int first);
int						ls_error(char *s, int error);
int						ls_namemax(t_file *lst);
int						display_list(t_file **lst, int flags);
char					get_sortkey(int flags);
void    				display_name(t_file *l, int flags, int block_len);
static int     			lst_column(t_file *lst, t_index row_col, t_index maxlen, int flags);
static int  			display_basic_list(t_file *lst, int flags);
int						free_list_content(t_file **lst);
int						ls_namemax(t_file *lst);
t_file					*lst_swap(t_file *p1, t_file *p2);
t_file  				*sorted_merge(t_file *a, t_file *b, int key);
void    				front_back_split(t_file *source, t_file **front_ref, t_file **back_ref);
void    				merge_sort(t_file **head_ref, int key);
t_file  				*timesort_merge(t_file *a, t_file *b, int key);
t_file  				*namesort_merge(t_file *a, t_file *b, int key);

//display
int         			display_all(t_file *begin, int flags, int first, int n);
void					display_name(t_file *l, int flags, int blocks_len);
int    	 				display_long(t_file *lst, int flags);


int				sort_list(t_file **begin, short flags);



#   endif
