/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoodale <egoodale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/27 15:40:52 by egoodale          #+#    #+#             */
/*   Updated: 2018/05/31 12:57:18 by egoodale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

t_file	*namesort_merge(t_file *a, t_file *b, int key)
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

t_file	*timesort_merge(t_file *a, t_file *b, int key, t_bool delta)
{
	VAR(t_file *, result, NULL);
	VAR(unsigned long, a_time, delta ? a->ntime : a->time);
	VAR(unsigned long, b_time, delta ? b->ntime : b->time);
	if (a_time == b_time && !delta)
		return (timesort_merge(a, b, key, true));
	else if (!(key & f_revsort) ? (a_time > b_time) :
			(a_time < b_time))
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

t_file	*sorted_merge(t_file *a, t_file *b, int key, t_bool timesort_delta)
{
	VAR(t_file *, result, NULL);
	if (a == NULL)
		return (b);
	else if (b == NULL)
		return (a);
	if (key & f_timsort)
		result = timesort_merge(a, b, key, timesort_delta);
	else
		result = namesort_merge(a, b, key);
	return (result);
}

void	front_back_split(t_file *source, t_file **front_ref, t_file **back_ref)
{
	VAR(t_file *, slow, source);
	VAR(t_file *, fast, source->next);
	while (fast)
	{
		fast = fast->next;
		if (fast)
		{
			slow = slow->next;
			fast = fast->next;
		}
	}
	*front_ref = source;
	*back_ref = slow->next;
	slow->next = NULL;
}

void	merge_sort(t_file **head_ref, int key)
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
