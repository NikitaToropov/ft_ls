#include "ft_ls.h"

static void	del_t_node(t_node **node)
{
	if (!*node)
		return ;
	if ((*node)->name)
		free((*node)->name);
	if ((*node)->path)
		free((*node)->path);
	if ((*node)->sym_link)
		free((*node)->sym_link);
	if ((*node)->owner_name)
		free((*node)->owner_name);
	free(*node);
	*node = NULL;
}

t_node		*new_t_dir(char *name, t_node *parent)
{
	t_node	*new;

	MEM_CHECK((new = ft_memalloc(sizeof(t_node))));
	new->name = ft_strdup(name);
	new->parent = parent;
	new->path = ft_pathjoin((parent)
							? parent->path
							: NULL, new->name);
	return (new);
}

void		del_line_of_nodes(t_node **head)
{
	t_node	*next;
	t_node	*curr;

	if (!head || !*head)
		return ;
	curr = *head;
	while (curr)
	{
		next = curr->next;
		del_t_node(&curr);
		curr = next;
	}
	*head = NULL;
}

void		insert(t_node **head, t_node *new,
			char comparator(const t_node *, const t_node *))
{
	t_node	*prev;
	t_node	*next;

	if (!*head)
		*head = new;
	else
	{
		prev = NULL;
		next = *head;
		while (next && comparator(next, new) == LESS)
		{
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

void		insert_order_by(t_node **head, t_node *new, unsigned short flags)
{
	if (!head || !new)
		return ;
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
