/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoodale <egoodale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/26 11:46:50 by egoodale          #+#    #+#             */
/*   Updated: 2018/05/29 15:02:30 by egoodale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

t_file	*init_file_lst(char **av, int ac, int first)
{
	VAR(t_file *, head, NULL);
	VAR(int, i, -1);

	if (ac == 0)
		add_new_file("", ".", &head);
	else	
		ft_sortwords(av, (size_t)ac);
	while (++i < ac)
		if (add_new_file("", av[i], &head) == -1 && first)
			ls_error(av[i], ERRNO);
	return (head);
}

int		check_args(int ac, char **av, int *flags)
{
	int		i;
	int		j;

	*flags = 0;
	i = 0;
	while(++i < ac && av[i][0] == '-')
	{
		j = 0;
		while(av[i][++j])
		{
			*flags |= av[i][j] == 'l' ? f_lngform : *flags;
			*flags |= av[i][j] == 'R' ? f_recurse : *flags;
			*flags |= av[i][j] == 'a' ? f_seedots : *flags;
			*flags |= av[i][j] == 'r' ? f_revsort : *flags;
			*flags |= av[i][j] == 't' ? f_timsort : *flags;
			*flags |= av[i][j] == '@' ? f_prntatr : *flags;
			*flags |= av[i][j] == 'G' ? f_coloset : *flags;
			*flags |= av[i][j] == 'd' ? f_nmeonly : *flags;
		}
	}
	return (i);
}

int main(int ac, char **av)
{
	t_file *file_lst;
    int flags;
	int i;
	int		nofiles = 0;

    if((i = check_args(ac, av, &flags)) < 0)
        return (1);
	ac -= i;
    av += i;
	file_lst = init_file_lst(av, ac, 1);
	nofiles = (!file_lst ? 1 : 0);
	display_all(file_lst, flags, (!nofiles ? 1 : 2), ac);
	free_list_content(&file_lst);
	return (0);
}