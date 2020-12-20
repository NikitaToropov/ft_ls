#include "ft_ls.h"

void del_t_node(t_node **node)
{
	if (!*node)
		return;
	if ((*node)->name)
		free((*node)->name);
	if ((*node)->path)
		free((*node)->path);
	if ((*node)->sym_link)
		free((*node)->sym_link);
	if ((*node)->group_name)
		free((*node)->group_name);
	if ((*node)->owner_name)
		free((*node)->owner_name);
	free(*node);
	*node = NULL;
}

t_node *new_t_dir(char *name, t_node *parent)
{
	t_node *new;

	MEM_CHECK((new = ft_memalloc(sizeof(t_node))));
	new->name = ft_strdup(name);
	new->parent = parent;
	new->path = ft_pathjoin((parent)
							? parent->path
							: NULL, new->name);
	return (new);
}

t_node *push_back(t_node **head, char *name, t_node *parent)
{
	t_node *new_node;
	t_node *tmp;

	MEM_CHECK((new_node = new_t_dir(name, parent)));
	if (*head == NULL)
		*head = new_node;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_node;
	}
	return new_node;
}

void del_line_of_nodes(t_node *head)
{
	t_node *next;

	while (head)
	{
		next = head->next;
		del_t_node(&head);
		head = next;
	}
}

//void del_nodes_recur(t_node *head)
//{
//	t_node *curr;
//	t_node *tmp;
//
//	curr = head;
//	while (curr)
//	{
//		del_nodes_recur(curr->content);
//		tmp = curr;
//		curr = curr->next;
//		del_t_node(&tmp);
//	}
//}


void insert(t_node **head, t_node *new,
			char comparator(const t_node *, const t_node *))
{
	t_node *prev;
	t_node *next;

	if (!head || !new)
		return;
	if (!*head)
		*head = new;
	else
	{
		prev = NULL;
		next = *head;
		while (next)
		{
			if (comparator(next, new) == MORE)
				break;
			prev = next;
			next = next->next;
		}
		if (prev == NULL)
		{
			new->next = *head;
			*head = new;
		}
		else
		{
			prev->next = new;
			new->next = next;
		}
	}
}

void insert_order_by(t_node **head, t_node *new, unsigned short flags)
{
	if (!head || !new)
		return;
	else if (flags & get_flag_code('f'))
		insert(head, new, default_for_pushing_back);
	else if (flags & get_flag_code('t'))
	{
		if (flags & get_flag_code('r'))
			insert(head, new, compare_by_date_reverse);
		else
			insert(head, new, compare_by_date);
	}
	else
	{
		if (flags & get_flag_code('r'))
			insert(head, new, compare_lexicographic_reverse);
		else
			insert(head, new, compare_lexicographic);
	}
}
