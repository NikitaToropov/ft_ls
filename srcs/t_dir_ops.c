#include "ft_ls.h"

void del_t_dir(t_dir *node)
{
	if (!node)
		return;
	if (node->name)
		free(node->name);
	if (node->path)
		free(node->path);
//	if (node->description.fie_group)
//		free(node->description.fie_group);
//	if (node->description.owner_name)
//		free(node->description.owner_name);
	free(node);
}

t_dir *new_t_dir(char *name, t_dir *parent)
{
	t_dir *new;

	MEMCHECK((new = ft_memalloc(sizeof(t_dir))));
	new->name = ft_strdup(name);
	new->parent = parent;
	new->path = ft_pathjoin((parent)
							? parent->path
							: NULL, name);
	return (new);
}

void push_front(t_dir **head, char *name, t_dir *parent)
{
	t_dir *new_node;

	MEMCHECK((new_node = new_t_dir(name, parent)));
	new_node->next = *head;
	*head = new_node;
}

void del_t_dirs_recur(t_dir *head)
{
	t_dir *curr;
	t_dir *tmp;

	curr = head;
	while(curr)
	{
		del_t_dirs_recur(curr->content);
		tmp = curr;
		curr = curr->next;
		del_t_dir(tmp);
	}
}
