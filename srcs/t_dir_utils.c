#include "ft_ls.h"

void del_t_dir(t_node **node)
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

void push_back(t_node **head, char *name, t_node *parent)
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
}

void del_nodes_recur(t_node *head)
{
	t_node *curr;
	t_node *tmp;

	curr = head;
	while (curr)
	{
		del_nodes_recur(curr->content);
		tmp = curr;
		curr = curr->next;
		del_t_dir(&tmp);
	}
}
