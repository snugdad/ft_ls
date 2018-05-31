/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoodale <egoodale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/26 11:46:50 by egoodale          #+#    #+#             */
/*   Updated: 2018/05/30 22:34:01 by egoodale         ###   ########.fr       */
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

unsigned	resolve_flag(int c)
{
	VAR(unsigned, ret, 0);

	ret |= c == 'l' ? f_lngform : 0;
	ret |= c == 'R' ? f_recurse : 0;
	ret |= c == 'a' ? f_seedots : 0;
	ret |= c == 'r' ? f_revsort : 0;
	ret |= c == 't' ? f_timsort : 0;
	ret |= c == '@' ? f_prntatr : 0;
	ret |= c == 'G' ? f_coloset : 0;
	ret |= c == 'd' ? f_nmeonly : 0;
	return (ret);
}

int		check_args(int ac, char **av, int *flags, int *error)
{
	VAR(int, i, 0);
	VAR(int, j, 0);
	
	while(++i < ac && av[i][0] == '-')
	{
		j = 0;
		while(av[i][++j])
		{
			if (ft_strchr(LS_VALID_ARGS, av[i][j]))
				*flags |= resolve_flag(av[i][j]);
			else
				ls_error(&av[i][j], USAGE);
		}
	}
	return (i);
}

int main(int ac, char **av)
{
	VAR(t_file *, files, NULL);
    VAR(int, flags, 0);
	VAR(int, i, 0);
	VAR(int, error, 0);

    i = check_args(ac, av, &flags, &error);
	ac -= i;
    av += i;
	files = init_file_lst(av, ac, 1);
	display_all(files, flags, (files ? 1 : 2), ac);
	free_list_content(&files);
	return (0);
}