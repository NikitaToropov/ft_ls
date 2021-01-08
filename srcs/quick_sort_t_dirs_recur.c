/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quick_sort_t_dirs_recur.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmissy <cmissy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 16:54:10 by cmissy            #+#    #+#             */
/*   Updated: 2021/01/08 17:51:42 by enikole          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quick_sort_t_dirs_recur.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmissy <cmissy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 16:54:10 by cmissy            #+#    #+#             */
/*   Updated: 2021/01/08 17:50:56 by enikole          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_node			*get_tail(t_node *node)
{
	while (node && node->next)
		node = node->next;
	return (node);
}

t_node			*partition(t_node *head, t_node *end, t_node **new_head,
							t_node **new_end,
							char comparator(const t_node *, const t_node *))
{
	t_node *pivot;
	t_node *prev;
	t_node *cur;
	t_node *tail;
	t_node *tmp;

	pivot = end;
	prev = NULL;
	cur = head;
	tail = pivot;
	while (cur != pivot)
	{
		if (comparator(cur, pivot) == LESS)
		{
			*new_head = (*new_head == NULL) ? cur : *new_head;
			prev = cur;
			cur = cur->next;
		}
		else
		{
			if (prev)
				prev->next = cur->next;
			tmp = cur->next;
			cur->next = NULL;
			tail->next = cur;
			tail = cur;
			cur = tmp;
		}
	}
	*new_head = (*new_head == NULL) ? pivot : *new_head;
	*new_end = tail;
	return (pivot);
}

t_node			*quick_sort_nodes_recur(t_node *head, t_node *end,
								char comparator(const t_node *, const t_node *))
{
	t_node		*new_head;
	t_node		*new_end;
	t_node		*pivot;
	t_node		*tmp;

	if (!head || head == end || !comparator)
		return (head);
	new_head = NULL;
	new_end = NULL;
	pivot = partition(head, end, &new_head, &new_end, comparator);
	if (new_head != pivot)
	{
		tmp = new_head;
		while (tmp->next != pivot)
			tmp = tmp->next;
		tmp->next = NULL;
		new_head = quick_sort_nodes_recur(new_head, tmp, comparator);
		tmp = get_tail(new_head);
		tmp->next = pivot;
	}
	pivot->next = quick_sort_nodes_recur(pivot->next, new_end, comparator);
	return (new_head);
}

void			nodes_sorting_by_flags(t_node **head, unsigned short flags)
{
	if (flags & get_flag_code('f') || !head || !*head)
		return ;
	else if (flags & get_flag_code('t'))
	{
		if (flags & get_flag_code('r'))
			*head = quick_sort_nodes_recur(*head, get_tail(*head),
											compare_by_date_reverse);
		else
			*head = quick_sort_nodes_recur(*head, get_tail(*head),
											compare_by_date);
	}
	else
	{
		if (flags & get_flag_code('r'))
			*head = quick_sort_nodes_recur(*head, get_tail(*head),
											compare_lexicographic_reverse);
		else
			*head = quick_sort_nodes_recur(*head, get_tail(*head),
											compare_lexicographic);
	}
}
