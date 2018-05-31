/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoodale <egoodale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 19:03:21 by egoodale          #+#    #+#             */
/*   Updated: 2018/05/31 14:06:49 by egoodale         ###   ########.fr       */
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

#define LS_VALID_ARGS "lRartGd"
#define ACL_BUFFERMAX 101
#define PATH_MAX 1024

typedef struct stat		t_stat;
typedef struct dirent	t_dirent;
typedef struct passwd	t_passwd;
typedef struct group	t_group;
typedef struct ttysize	t_ittys;

enum {ERRNO, USAGE, MALL_ERR};

typedef enum    e_lsflag
{
    f_lngform = (1 << 0),
    f_recurse = (1 << 1),
    f_seedots = (1 << 2),
    f_revsort = (1 << 3),
    f_timsort = (1 << 4),
	f_coloset = (1 << 5),	
	f_nmeonly = (1 << 6),	
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
	mode_t			st_mode;
	nlink_t			st_nlink;
	uid_t			st_uid;
	gid_t			st_gid;
	dev_t			st_rdev;
	off_t			st_size;
	time_t			time;
	long			ntime;
	blkcnt_t		st_blocks;
	struct s_file	*next;
}					t_file;

/*
** main.c
*/
int						check_args(int ac, char **av, int *flags, int *error);
unsigned				resolve_flag(int c);
t_file					*init_file_lst(char **av, int ac, int first);

/*
** build_files.c
*/
char					get_file_acl(char path[PATH_MAX]);
static inline int		build_full_path(char path[PATH_MAX], char *name,
										char full_path[PATH_MAX]);
static inline t_file	*create_new_file(char path[PATH_MAX], char *name, t_stat *stat);
int						add_new_file(char path[PATH_MAX], char *name, t_file **lst);
/*
** display.c
*/
int						display_all(t_file *begin, int flags, int first, int n);
static  void			display_full_path(char *full_path, int nof, int *first);
static  t_file			*read_folder(char path[PATH_MAX], char *name, int options);

/*
** display_lngform.c
*/
static inline char		get_file_type(int mode);
static void				populate_chmod(char chmod[12], int mode, char path[PATH_MAX]);
int						display_list_items(t_file *file, size_t size[7], int flags);
int						get_vector_size(t_file *file, size_t size[7], int *blocks);
int						display_long(t_file *lst, int flags);

/*
** display_basic.c
*/
int						display_list(t_file **lst, int flags);
static int				display_basic(t_file *lst, int flags);
static int				lst_column(t_file *lst, t_coord rc, t_coord max, int flags);
void					display_name(t_file *l, int flags, int len);
unsigned				get_lst_len(t_file *lst);

/*
** ls_sort.c
*/
void					merge_sort(t_file **head_ref, int key);
void					front_back_split(t_file *source, t_file **front_ref, t_file **back_ref);
t_file					*sorted_merge(t_file *a, t_file *b, int key, t_bool timesort_delta);
t_file					*timesort_merge(t_file *a, t_file *b, int key, t_bool delta);
t_file					*namesort_merge(t_file *a, t_file *b, int key);

/*
** misc.c
*/
void					display_time(t_file *file);
int						ls_namemax(t_file *lst);
int						free_list_content(t_file **lst);
int						ls_error(char *s, int error);



#   endif
