/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoodale <egoodale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 18:54:39 by egoodale          #+#    #+#             */
/*   Updated: 2018/05/19 15:59:56 by egoodale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/ft_ls.h"



char		valid_arg(char c)
{
	return (c == 'l' || c == 'R' || c == 'a' ||
			c == 'r' || c == 't');
}

ssize_t	str_is_chr(char *s, char c)
{
	ssize_t count;

	count = 0;
	while(*s && (*s == c || *s == '/'))
	{	
		if(*s == c)
			count++;
		s++;
	}
	return (!*s ? (count / 2) : -1);
}

char	*chop_path(char *path, size_t chop_count)
{
	char *ret;
	ssize_t len;

	len = (ssize_t)strlen(path);
	while(--len >= 0 && chop_count > 0)
		if(path[len] == '/')
			chop_count--;
	ret = strndup(path, (&path[len] - path) + 1);
	free (path);
	path = ret;
	return (path);
}

char	*get_path(char *target)
{
	char *path;
	ssize_t	dot_count;

	if (!(path = (char *)malloc(sizeof(char) * 1024)))
		throw_err("MALLOC ERROR");
	if(!getcwd(path, 1024))
		throw_err("getcwd error");
	if(target)
	{
		if((dot_count = str_is_chr(target, '.')) > 1)
			return(chop_path(path, (size_t)dot_count));
		else
		{		
			strcat(path, "/");
			strcat(path, target);
		}
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