/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoodale <egoodale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 19:03:21 by egoodale          #+#    #+#             */
/*   Updated: 2018/05/17 14:25:56 by egoodale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#   ifndef FT_LS_H
#   define FT_LS_H

#include <dirent.h>

typedef enum    e_flag
{
    l = (1 << 0),
    R = (1 << 1),
    a = (1 << 2),
    r = (1 << 3),
    t = (1 << 4),
	@ = (1 << 5)
}               t_flag;

typedef struct	s_inode
{
	char *permissions;
	char type;
	unsigned children;
	char *owner;
	char *group;
	size_t size;
	char *name;
	unsigned long serial_nb;
}				t_inode;
char			check_args(char **arg_list, char *target);
#   endif