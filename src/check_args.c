/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoodale <egoodale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 18:54:39 by egoodale          #+#    #+#             */
/*   Updated: 2018/05/17 14:47:31 by egoodale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/ft_ls.h"

char		valid_arg(char c)
{
	return (c == 'l' || c == 'R' || c == 'a' ||
			c == 'r' || c == 't');
}

char    check_args(char **arg_lst, char *path)
{
	int		i;
	int		j;
	char	flags;
	i = 0;
	while(arg_lst[++i][0] == '-'])
	{
		j = 0;
		while(valid_arg(arg_lst[i][++j]))
		{
			flags = arg_lst[i][j] == 'l' ? flags | l : flags;
			flags = arg_lst[i][j] == 'R' ? flags | R : flags;
			flags = arg_lst[i][j] == 'a' ? flags | a : flags;
			flags = arg_lst[i][j] == 'r' ? flags | r : flags;
			flags = arg_lst[i][j] == 't' ? flags | t : flags;
			flags = arg_lst[i][j] == '@' ? flags | @ : flags;	
		}
	}
	path = arg_lst[i] ? arg_lst[i] : ".";
	return (flags);
}