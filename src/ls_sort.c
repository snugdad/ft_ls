/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoodale <egoodale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/27 15:40:52 by egoodale          #+#    #+#             */
/*   Updated: 2018/05/30 15:12:35 by egoodale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"
/*
static t_file	*timesort(t_file *lst)
{
	if (!lst)
		return (NULL);
	if (lst->next && (lst->time < lst->next->time))
		lst = lst_swap(lst, lst->next);
	else if (lst->next && lst->time == lst->next->time)
		if (lst->next && (lst->ntime < lst->next->ntime))
			lst = lst_swap(lst, lst->next);
	lst->next = lst_sort_time(lst->next);
	if (lst->next && (lst->time < lst->next->time))
	{
		lst = lst_swap(lst, lst->next);
		lst->next = lst_sort_time(lst->next);
	}
	else if (lst->next && lst->time == lst->next->time)
	{
		if (lst->next && (lst->ntime < lst->next->ntime))
		{
			lst = lst_swap(lst, lst->next);
			lst->next = lst_sort_time(lst->next);
		}
	}
	return (ls
	*/

t_file  *namesort_merge(t_file *a, t_file *b, int key)
{
    VAR(t_file *, result, NULL);
    
    if (!(key & f_revsort) ? (ft_strcmp(a->name, b->name) < 0) : 
        (ft_strcmp(a->name, b->name) > 0))
    {
        result = a;
        result->next = sorted_merge(a->next, b, key, false);
    }
    else
    {
        result = b;
        result->next = sorted_merge(a, b->next, key, false);
    }
    return (result);
}

t_file  *timesort_merge(t_file *a, t_file *b, int key, t_bool delta)
{
    VAR(t_file *, result, NULL);
    VAR(unsigned long, a_time, delta ? a->ntime : a->time);
	VAR(unsigned long, b_time, delta ? b->ntime : b->time);
    
	if (a_time == b_time && !delta)
		return (timesort_merge(a, b, key, true));
    else if	(a_time > b_time)
    {
        result = !(key & f_revsort) ? a : b;
        result->next = !(key & f_revsort) ? sorted_merge(a->next, b, key, false) :
											sorted_merge(a, b->next, key, false);
    }
    else
    {
        result = !(key & f_revsort) ? b : a;
        result->next = !(key & f_revsort) ? sorted_merge(a, b->next, key, false) :
											sorted_merge(a->next, b, key, false);
    }
    return (result);
}

t_file  *sorted_merge(t_file *a, t_file *b, int key, t_bool timesort_delta)
{
    VAR(t_file *, result, NULL);
    
    if (a == NULL)
        return(b);
    else if (b == NULL)
        return (a);
    if (key & f_timsort)
        result = timesort_merge(a, b, key, timesort_delta);
    else
        result = namesort_merge(a, b, key);
    return(result);
}

void    front_back_split(t_file *source, t_file **front_ref, t_file **back_ref)
{
    VAR(t_file *, slow, source);
    VAR(t_file *, fast, source->next);

    while(fast)
    {
        fast = fast->next;
        if(fast)
        {
            slow = slow->next;
            fast = fast->next;
        }
    }
    *front_ref = source;
    *back_ref = slow->next;
    slow->next = NULL;
}

void    merge_sort(t_file **head_ref, int key)
{
    VAR(t_file *, head, *head_ref);
    VAR(t_file *, a, NULL);
    VAR(t_file *, b, NULL);

    if ((head == NULL) || (head->next == NULL))
        return ;
    front_back_split(head, &a, &b);
    merge_sort(&a, key);
    merge_sort(&b, key);
    *head_ref = sorted_merge(a, b, key, false);
}



/*
static t_file	*lst_sort_ascii(t_file *lst)
{
	if (!lst)
		return (NULL);
	if (lst->next && ft_strcmp(lst->name, lst->next->name) > 0)
		lst = lst_swap(lst, lst->next);
	lst->next = lst_sort_ascii(lst->next);
	if (lst->next && ft_strcmp(lst->name, lst->next->name) > 0)
	{
		lst = lst_swap(lst, lst->next);
		lst->next = lst_sort_ascii(lst->next);
	}
	return (lst);
}


static t_file	*lst_sort_time(t_file *lst)
{
	if (!lst)
		return (NULL);
	if (lst->next && (lst->time < lst->next->time))
		lst = lst_swap(lst, lst->next);
	else if (lst->next && lst->time == lst->next->time)
		if (lst->next && (lst->ntime < lst->next->ntime))
			lst = lst_swap(lst, lst->next);
	lst->next = lst_sort_time(lst->next);
	if (lst->next && (lst->time < lst->next->time))
	{
		lst = lst_swap(lst, lst->next);
		lst->next = lst_sort_time(lst->next);
	}
	else if (lst->next && lst->time == lst->next->time)
	{
		if (lst->next && (lst->ntime < lst->next->ntime))
		{
			lst = lst_swap(lst, lst->next);
			lst->next = lst_sort_time(lst->next);
		}
	}
	return (lst);
}

static t_file	*lst_sort_size(t_file *lst)
{
	if (!lst)
		return (NULL);
	if (lst->next && (lst->st_size < lst->next->st_size))
		lst = lst_swap(lst, lst->next);
	lst->next = lst_sort_size(lst->next);
	if (lst->next && (lst->st_size < lst->next->st_size))
	{
		lst = lst_swap(lst, lst->next);
		lst->next = lst_sort_size(lst->next);
	}
	return (lst);
}




int				sort_list(t_file **begin, short flags)
{
	*begin = lst_sort_ascii(*begin);
	if (flags & f_timsort)
		*begin = lst_sort_time(*begin);
	if (flags & 256)
		*begin = lst_sort_size(*begin);
	if (flags & f_revsort)
		*begin = ft_reverse_lst(*begin);
	return (1);
}*/