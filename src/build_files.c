/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoodale <egoodale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/26 14:18:42 by egoodale          #+#    #+#             */
/*   Updated: 2018/05/31 14:00:15 by egoodale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

char					get_file_acl(char path[PATH_MAX])
{
	char		buf[ACL_BUFFERMAX];
	acl_t		acl;
	acl_entry_t dummy;

	if (listxattr(path, buf, ACL_BUFFERMAX, XATTR_NOFOLLOW))
		return ('@');
	if ((acl = acl_get_link_np(path, ACL_TYPE_EXTENDED)))
		if (acl && (acl_get_entry(acl, ACL_FIRST_ENTRY, &dummy) == -1))
		{
			acl_free(acl);
			acl = NULL;
			return ('+');
		}
	return (' ');
}

static inline int		build_full_path(char path[PATH_MAX], char *name,
										char full_path[PATH_MAX])
{
	VAR(int, i, -1);
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

static inline t_file	*create_new_file(char path[PATH_MAX], char *name,
										t_stat *stat)
{
	t_file	*new;

	if (!(new = (t_file*)ft_memalloc(sizeof(t_file)))
	|| (!(new->name = ft_strdup(name))))
		ls_error(NULL, 2);
	new->st_mode = stat->st_mode;
	new->st_nlink = stat->st_nlink;
	new->st_uid = stat->st_uid;
	new->st_gid = stat->st_gid;
	new->st_size = stat->st_size;
	new->st_rdev = stat->st_rdev;
	new->time = stat->st_mtimespec.tv_sec;
	new->ntime = stat->st_mtimespec.tv_nsec;
	new->st_blocks = stat->st_blocks;
	build_full_path(path, name, new->full_path);
	new->next = NULL;
	return (new);
}

int						add_new_file(char path[PATH_MAX], char *name,
									t_file **lst)
{
	char	full_path[PATH_MAX];
	t_stat	stat;

	if (!(build_full_path(path, name, full_path)))
	{
		ls_error(name, 1);
		return (FAILURE);
	}
	if (lstat(full_path, &stat) < 0)
		return (FAILURE);
	if (!*lst)
		*lst = create_new_file(path, name, &stat);
	else
	{
		while ((*lst)->next)
			lst = &((*lst)->next);
		(*lst)->next = create_new_file(path, name, &stat);
	}
	return (SUCCESS);
}
