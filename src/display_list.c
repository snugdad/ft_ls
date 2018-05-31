/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoodale <egoodale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/27 16:26:12 by egoodale          #+#    #+#             */
/*   Updated: 2018/05/31 13:08:57 by egoodale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

unsigned	get_lst_len(t_file *lst)
{
	VAR(unsigned, i, 0);
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

void		display_name(t_file *l, int flags, int len)
{
	VAR(int, pad_size, MAX(len - ft_intlen(l->st_blocks), 0));
	VAR(char *, padblk, (char*)malloc(sizeof(pad_size + 1)));
	if (len)
	{
		ft_printf("%s", padblk);
		ft_printf("%d ", l->st_blocks);
	}
	if (flags & f_coloset)
	{
		if (S_ISDIR(l->st_mode))
			ft_printf("{bcyan}%s{eoc}", l->name);
		else
			ft_printf((S_IXUSR & l->st_mode) ? "{red}%s{eoc}" : "%s", l->name);
	}
	else
		ft_printf("%s", l->name);
	free(padblk);
}

static int	lst_column(t_file *lst, t_coord rc, t_coord max, int flags)
{
	VAR(int, tmp_column, 0);
	VAR(int, tmp_row, 0);
	VAR(t_file *, tmp, NULL);
	VAR(int, counter, rc.y);
	while (lst && counter--)
	{
		tmp_column = rc.x;
		tmp = lst->next;
		while (lst && tmp_column--)
		{
			display_name(lst, flags, max.y);
			if (tmp_column)
				ft_putnchar(MAX(max.x - ft_strlen(lst->name), 0), ' ');
			tmp_row = rc.y;
			while (lst && tmp_row--)
				lst = lst->next;
		}
		ft_printf("\n");
		lst = tmp;
	}
	return (1);
}

static int	display_basic(t_file *lst, int flags)
{
	t_coord			i;
	t_ittys			ts;
	t_coord			max;
	int				total;

	total = 0;
	max.x = ls_namemax(lst) + 2;
	max.y = 0;
	ioctl(STDIN_FILENO, TIOCGWINSZ, &ts);
	i.x = ts.ts_cols / (max.x + max.y);
	i.y = get_lst_len(lst);
	i.y = !!(i.y % i.x) + (i.y / i.x);
	lst_column(lst, i, max, flags);
	return (SUCCESS);
}

int			display_list(t_file **lst, int flags)
{
	merge_sort(lst, flags);
	(flags & f_lngform) ? display_long(*lst, flags) :
	display_basic(*lst, flags);
	return (SUCCESS);
}
