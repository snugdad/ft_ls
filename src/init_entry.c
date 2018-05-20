/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_entry.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoodale <egoodale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/19 19:50:17 by egoodale          #+#    #+#             */
/*   Updated: 2018/05/19 20:51:32 by egoodale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

int			is_directory(const char *path, t_stat *statbuf)
{
	if (stat(path, statbuf) != 0)
		return (0);
	return (S_ISDIR(statbuf.st_mode));
}

t_list		get_children(char path[PATH_MAX], char flags)
{
	t_list		*first_child;
	DIR			*dir;
	t_dirent	*dp;
	VAR(unsigned, count, 0);
	char		full_path[PATH_MAX];
	t_entry		*new_entry

	first_child = ft_lstnew(NULL, 0);
	dir = opendir(full_path);
	while((dp = readdir(dir)))
	{
		get_full_path(path, dp->d_name, full_path);
		if(is_directory(full_path))
		{
			new_entry = create_new_entry(full_path, dp->d_name, statbuf, flags);
			first_child = ft_lstpushback(&first_child, ft_lstnew(new_entry, sizeof(*new_entry)));
		}
		
		if(flags & a && dp->dname[0] == '.')

	}





	dir = opendir(full_path);

}



static inline int		get_full_path(char path[PATH_MAX], char *name,
						char full_path[PATH_MAX])__attribute__((always_inline))
{
	int	i;

	i = -1;
	while (path[++i])
		full_path[i] = path[i];
	if (i && i < PATH_MAX)
		if (!(path[0] == '/' && path[1] == '\0'))
			full_path[i++] = '/';
	while (*name && i < PATH_MAX)
		full_path[i++] = *name++;
	if (i < PATH_MAX)
		full_path[i] = '\0';
	else
		errno = ENAMETOOLONG;
	return ((i < PATH_MAX) ? 1 : 0);
}

t_entry		*create_new_entry(char path[PATH_MAX], char *target, t_stat *stat, char flags)
{
	t_entry	*ret;

	if (!(new = (t_entry *)malloc(sizeof(t_entry))) ||
 	(!(new->name = ft_strdup(target))))
    	throw_err("Malloc Error");
	ret->st_dev = stat->st_dev;
	ret->st_ino = stat->st_ino;
	ret->st_mode = stat->st_mode;
	ret->st_nlink = stat->st_nlink;
	ret->st_uid = stat->st_uid;
	ret->st_gid = stat->st_gid;
	ret->st_rdev = stat->st_rdev;
	ret->st_size = stat->st_size;
	ret->st_blksize= stat->st_blksize
	ret->st_blocks = stat->st_blocks;
	get_full_path(path, name, ret->full_path);
	ret->next = NULL;
	if (flags & R)
		ret->children = get_children(ret->full_path);
	return (new);
}