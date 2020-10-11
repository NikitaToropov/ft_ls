#include "ft_ls.h"

void del_t_dir(t_dir *node)
{
	if (!node)
		return;
	if (node->name)
		free(node->name);
//	if (node->description.fie_group)
//		free(node->description.fie_group);
//	if (node->description.owner_name)
//		free(node->description.owner_name);
	free(node);
}

t_dir *new_t_dir(char *name)
{
	t_dir *new;

	MEMCHECK((new = ft_memalloc(sizeof(t_dir))));
	new->name = name;
	return (new);
}

void push_front(t_dir **head, char *name)
{
	t_dir *new_node;

	new_node = new_t_dir(name);
	new_node->next = *head;
	*head = new_node;
}

void del_t_dirs_recur(t_dir **head)
{
	t_dir *curr;
	t_dir *tmp;

	curr = *head;
	*head = NULL;
	while (curr)
	{
		del_t_dirs_recur(&(curr->content));
		tmp = curr;
		del_t_dir(tmp);
		curr = curr->next;
	}
}
