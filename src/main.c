/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoodale <egoodale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 18:47:40 by egoodale          #+#    #+#             */
/*   Updated: 2018/05/17 14:53:21 by egoodale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/xattr.h>

auto int		throw_err(char *msg)
{
	printf("%s\n", msg);
	exit(0);
}

int main(int ac, char **av)
{
    char flags;
	char *path;

    if((flags = check_args(av)) < 0)
        throw_err("INCORRECT ARGUMENT FORMAT");
    

	
	//printf("%i\n", (int)flags);
}

