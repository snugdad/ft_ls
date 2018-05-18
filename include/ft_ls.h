/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoodale <egoodale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 19:03:21 by egoodale          #+#    #+#             */
/*   Updated: 2018/05/17 17:16:59 by egoodale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#   ifndef FT_LS_H
#   define FT_LS_H

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/xattr.h>
#include <sys/stat.h>
#include <unistd.h>

typedef enum    e_flag
{
    l = (1 << 0),
    R = (1 << 1),
    a = (1 << 2),
    r = (1 << 3),
    t = (1 << 4),
	at = (1 << 5)
}               t_flag;

typedef struct		s_entry
{
	char			*path;
	struct stat		*e_data;
	struct passwd 	*usr_data;
	struct s_entry	*first_child;
	struct s_entry	*next_child;
}					t_entry;

char			check_args(char **arg_list, char **path, int ac);
int				throw_err(char *msg);
#   endif