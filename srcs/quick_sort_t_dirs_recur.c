#include "ft_ls.h"

t_dir *get_tail(t_dir *node)
{
	while (node && node->next)
		node = node->next;
	return (node);
}

t_dir *partition(t_dir *head, t_dir *end, t_dir **new_head, t_dir **new_end,
				 char comparator(const t_dir *, const t_dir *))
{
	t_dir *pivot;
	t_dir *prev;
	t_dir *cur;
	t_dir *tail;
	t_dir *tmp;

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

t_dir *quick_sort_t_dirs_recur(t_dir *head, t_dir *end,
							   char comparator(const t_dir *, const t_dir *))
{
	t_dir *new_head;
	t_dir *new_end;
	t_dir *pivot;
	t_dir *tmp;

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
		new_head = quick_sort_t_dirs_recur(new_head, tmp, comparator);
		tmp = get_tail(new_head);
		tmp->next = pivot;
	}
	pivot->next = quick_sort_t_dirs_recur(pivot->next, new_end, comparator);
	return (new_head);
}

void sort_t_dir_list(t_dir **head, unsigned short flags)
{
	(void) flags;
	*head = quick_sort_t_dirs_recur(*head, get_tail(*head),
									compare_lexicographic);
//	*head = quick_sort_t_dirs_recur(*head, get_tail(*head), comparator);
}
