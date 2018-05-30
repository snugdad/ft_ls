/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoodale <egoodale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/27 16:26:12 by egoodale          #+#    #+#             */
/*   Updated: 2018/05/30 13:45:11 by egoodale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

void	ft_putstr_free(char const *s)
{
	write(1, s, ft_strlen(s));
	free((void *)s);
}

void	ft_putnchar(int len, char c)
{
	char	*s;

	if (!(s = (char *)malloc(sizeof(char) * len + 1)))
		return ;
	s[len] = '\0';
	while (len--)
		s[len] = c;
	ft_putstr_free(s);
}

t_file			*ft_reverse_lst(t_file **lst)
{
	t_file *a;
	t_file *b;
	t_file *c;

	a = NULL;
	b = *lst;
	c = (*lst)->next;
	while (b)
	{
		c = b->next;
		b->next = a;
		a = b;
		b = c;
	}
	return (a);
}

/*void    display_name(t_file *l, int flags, int block_len)
{
    VAR(size_t, ch_dif, MAX((block_len - ft_intlen((intmax_t)l->st_blocks)), 0));
    VAR(char *, s, NULL);
    
    if (block_len)
    {
        s = ft_strfill(ft_strnew(ch_dif), ' ', ch_dif);
        ft_printf("%s%d ", l->st_blocks);    
    }
    if (flags & f_coloset)
    {
        if (S_ISDIR(l->st_mode))
            ft_printf("{cyan}%s{eoc}", l->name);
        else
            ft_printf((S_IXUSR & l->st_mode) ? "{red}%s{eoc}" : "%s", l->name);    
    }
    else
        ft_printf("%s", l->name);
    if (s)
        free(s);    
}*/
void		display_name(t_file *l, int flags, int blocks_len)
{
	if (blocks_len)
	{
		ft_putnchar(MAX(blocks_len - ft_intlen(l->st_blocks), 0), ' ');
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
}

static int  lst_column(t_file *lst, t_index row_col, t_index maxlen, int flags)
{
	int				tmp_column;
	int				tmp_row;
	t_file			*lst_tmp;
	int				counter;

	counter = row_col.y;
	while (lst && counter--)
	{
		tmp_column = row_col.x;
		lst_tmp = lst->next;
		while (lst && tmp_column--)
		{
			display_name(lst, flags, maxlen.y);
			if (tmp_column)
				ft_putnchar(MAX(maxlen.x - ft_strlen(lst->name), 0), ' ');
			tmp_row = row_col.y;
			while (lst && tmp_row--)
				lst = lst->next;
		}
		ft_putchar('\n');
		lst = lst_tmp;
	}
	return (1);
}


static int  display_basic_list(t_file *lst, int flags)
{
    t_index     maxlen;
    struct ttysize  ts;
    t_index     i;
    t_file      *tmp_lst;
    VAR(int, total, 0);

    maxlen.x = ls_namemax(lst) + ((flags & f_coloset) ? 1 : 4);
    maxlen.y = 0;
    ioctl(0, TIOCGWINSZ, &ts);
    i.x = MAX((ts.ts_cols / (maxlen.x + maxlen.y)), 1);
    i.y = 0;
    tmp_lst = lst;
    while (tmp_lst)
    {
        ++i.y;
        tmp_lst = tmp_lst->next;
    }
    i.y = !!(i.y % i.x) + (i.y / i.x);
    lst_column(lst, i, maxlen, flags);
    return (SUCCESS);
}

char   get_sortkey(int flags)
{
    VAR(char, sortkey, 0);

    if (flags & f_revsort)
        sortkey |= reverse;
    if (flags & f_timsort)
        sortkey |= by_time;
    return (sortkey);
}

int			display_list(t_file **lst, int flags)
{
    VAR(char, sortkey, get_sortkey(flags));
	int i = 0;
	merge_sort(lst, flags);
    //if(flags & f_timsort)

	//ft_printf("Files in list after merge timesort: \n");
	/*while (*lst)
	{
		ft_printf("{bgreen}%s{eoc}\n", (*lst)->name);
		*lst = (*lst)->next; 
	}*/
	if (flags & f_lngform)
		display_long(*lst, flags);
	else
   		display_basic_list(*lst, flags);
    return (SUCCESS);
}