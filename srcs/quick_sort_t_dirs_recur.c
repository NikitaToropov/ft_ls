/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quick_sort_t_dirs_recur.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmissy <cmissy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 16:54:10 by cmissy            #+#    #+#             */
/*   Updated: 2021/01/08 18:55:02 by cmissy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_node			*get_tail(t_node *node)
{
	while (node && node->next)
		node = node->next;
	return (node);
}

void			init_structure(t_quick_sort *structure, t_node *head,
								t_node *end)
{
	structure->pivot = end;
	structure->prev = NULL;
	structure->cur = head;
	structure->tail = structure->pivot;
	structure->tmp = NULL;
}

t_node			*partition(t_quick_sort qss, t_node **new_head,
							t_node **new_end,
							char comparator(const t_node *, const t_node *))
{
	while (qss.cur != qss.pivot)
	{
		if (comparator(qss.cur, qss.pivot) == LESS)
		{
			*new_head = (*new_head == NULL) ? qss.cur : *new_head;
			qss.prev = qss.cur;
			qss.cur = qss.cur->next;
		}
		else
		{
			if (qss.prev)
				qss.prev->next = qss.cur->next;
			qss.tmp = qss.cur->next;
			qss.cur->next = NULL;
			qss.tail->next = qss.cur;
			qss.tail = qss.cur;
			qss.cur = qss.tmp;
		}
	}
	*new_head = (*new_head == NULL) ? qss.pivot : *new_head;
	*new_end = qss.tail;
	return (qss.pivot);
}

t_node			*quick_sort_nodes_recur(t_node *head, t_node *end,
								char comparator(const t_node *, const t_node *))
{
	t_node			*new_head;
	t_node			*new_end;
	t_node			*pivot;
	t_node			*tmp;
	t_quick_sort	structure;

	if (!head || head == end || !comparator)
		return (head);
	new_head = NULL;
	new_end = NULL;
	init_structure(&structure, head, end);
	pivot = partition(structure, &new_head, &new_end, comparator);
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
