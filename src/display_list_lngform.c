/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_list_lngform.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoodale <egoodale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 20:35:43 by egoodale          #+#    #+#             */
/*   Updated: 2018/05/30 14:00:09 by egoodale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

static void	display_time(t_file *file)
{
	time_t today;
	char	*s;

	time(&today);
	s = ctime(&(file->time)) + 4;
	ft_printf(" %.12s ", s);
}

static char get_file_type(int mode)
{
	VAR(char, type, '-');

	if (S_ISDIR(mode))
		type = 'd';
	else if (S_ISLNK(mode))
		type = 'l';
	else if (S_ISBLK(mode))
		type = 'b';
	else if (S_ISCHR(mode))
		type = 'c';
	else if (S_ISSOCK(mode))
		type = 's';
	else if (S_ISFIFO(mode))
		type = 'p';
	return (type);
}

static char	get_file_acl(char path[PATH_MAX])
{
	VAR(acl_t, acl, NULL);
	VAR(acl_entry_t, dummy, NULL);
	char	buf[ACL_BUFFERMAX];

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
static void	populate_chmod(char chmod[12], int mode, char path[PATH_MAX])
{
	chmod[0] = get_file_type(mode);
	chmod[1] = (S_IRUSR & mode) ? 'r' : '-';
	chmod[2] = (S_IWUSR & mode) ? 'w' : '-';
	chmod[3] = (S_IXUSR & mode) ? 'x' : '-';
	chmod[4] = (S_IRGRP & mode) ? 'r' : '-';
	chmod[5] = (S_IWGRP & mode) ? 'w' : '-';
	chmod[6] = (S_IXGRP & mode) ? 'x' : '-';
	chmod[7] = (S_IROTH & mode) ? 'r' : '-';
	chmod[8] = (S_IWOTH & mode) ? 'w' : '-';
	chmod[9] = (S_IXOTH & mode) ? 'x' : '-';
	chmod[10] = get_file_acl(path);
	chmod[11] = '\0';
	if (S_ISUID & mode)
		chmod[3] = chmod[3] == '-' ? 'S' : 's';
	if (S_ISGID & mode)
		chmod[6] = chmod[6] == '-' ? 'S' : 's';
	if (S_ISVTX & mode)
		chmod[9] = chmod[9] == '-' ? 'T' : 't';
}

int     display_list_items(t_file *file, size_t size[7], int flags)
{
    char chmod[12];
    char buf[PATH_MAX + 1];

    populate_chmod(chmod, file->st_mode, file->full_path);
	ft_printf("%s %*hu",chmod, size[1], file->st_nlink);
	ft_printf(" %-*s", size[2], getpwuid(file->st_uid)->pw_name);
	ft_printf("  %-*s", size[3], getgrgid(file->st_gid)->gr_name);
	if(chmod[0] == 'c' || chmod[0] == 'b')
		ft_printf("%*d, %*d", size[5], (major(file->st_rdev)), size[6], (minor(file->st_rdev)));
	else
		ft_printf("  %*lld", size[4], file->st_size);
	display_time(file);
	if (chmod[0] == 'l')
	{
		ft_bzero(buf, PATH_MAX + 1);
		readlink(file->full_path, buf, PATH_MAX);
		ft_printf("%s -> %s", file->name, buf);
	}
	else
		display_name(file, flags, 0);
	return (SUCCESS);
}

int     get_vector_size(t_file *file, size_t size[7], int *blocks)
{
    int len;
    size[5] = 3;
    size[6] = 3;
    while (file)
    {
        size[0] = MAX(ft_intlen(file->st_blocks), size[0]);
        size[1] = MAX(ft_intlen(file->st_nlink), size[1]);
        size[2] = MAX(ft_strlen(getpwuid(file->st_uid)->pw_name), size[2]);
        size[3] = MAX(ft_strlen(getgrgid(file->st_gid)->gr_name), size[3]);
        if(S_ISCHR(file->st_mode))
        {
            size[5] = MAX(ft_intlen(major(file->st_rdev)), size[5]);
            size[6] = MAX(ft_intlen(minor(file->st_rdev)), size[6]);
            len = size[5] + size[6] + 2;
        }
        else
            len = ft_intlen(file->st_size);
		size[4] = MAX(len, size[4]);
		*blocks += file->st_blocks;
		file = file->next;
	}
        size[5] = MAX(size[4] - size[6] - 1, size[5]);
        return (SUCCESS);
}
int     display_long(t_file *lst, int flags)
{
    size_t field_width[7];
    VAR(int, blocks, 0);
    VAR(int, first, 1);

    ft_bzero(field_width, sizeof(field_width));
    get_vector_size(lst, field_width, &blocks);
    while(lst)
    {
        if (first && !(flags & f_nmeonly))
        {
            ft_printf("total: %d\n", blocks);
            first = 0;
        }
        display_list_items(lst, field_width, flags);
        ft_putchar('\n');
        lst = lst->next;
    }
    return (1);
}

