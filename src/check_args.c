/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoodale <egoodale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 18:54:39 by egoodale          #+#    #+#             */
/*   Updated: 2018/05/17 17:26:38 by egoodale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/ft_ls.h"

char		valid_arg(char c)
{
	return (c == 'l' || c == 'R' || c == 'a' ||
			c == 'r' || c == 't');
}

char	*get_path(char *arg_lst)
{
	char *path;

	if (!(path = (char *)malloc(sizeof(char) * 1024)))
		throw_err("MALLOC ERROR");
	if(!getcwd(path, 1024))
		throw_err("getcwd error");
	if(arg_lst)
	{
		strcat(path, "/");
		strcat(path, arg_lst);
	}	
	return (path);
}

char    check_args(char **arg_lst, char **path, int ac)
{
	int		i;
	int		j;
	char	flags;

	flags = 0;
	i = 0;
	while(++i < ac && arg_lst[i][0] == '-')
	{
		j = 0;
		while(valid_arg(arg_lst[i][++j]))
		{
			flags = arg_lst[i][j] == 'l' ? flags | l : flags;
			flags = arg_lst[i][j] == 'R' ? flags | R : flags;
			flags = arg_lst[i][j] == 'a' ? flags | a : flags;
			flags = arg_lst[i][j] == 'r' ? flags | r : flags;
			flags = arg_lst[i][j] == 't' ? flags | t : flags;
			flags = arg_lst[i][j] == '@' ? flags | at : flags;	
		}
	}
	*path = get_path(arg_lst[i]);    //DONT FORGET TO FREE ME 
	return (flags);
}