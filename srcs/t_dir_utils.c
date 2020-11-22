#include "ft_ls.h"

void del_t_dir(t_dir **node)
{
	if (!*node)
		return;
	if ((*node)->name)
		free((*node)->name);
	if ((*node)->path)
		free((*node)->path);
	if ((*node)->sym_link)
		free((*node)->sym_link);
	free(*node);
	*node = NULL;
}

t_dir *new_t_dir(char *name, t_dir *parent)
{
	t_dir *new;

	MEM_CHECK((new = ft_memalloc(sizeof(t_dir))));
	if (name[0] == '~')
		new->name = ft_strjoin(USER_N_T, name + 1);
	else
		new->name = ft_strdup(name);
	new->parent = parent;
	new->path = ft_pathjoin((parent)
							? parent->path
							: NULL, new->name);
	return (new);
}

void push_back(t_dir **head, char *name, t_dir *parent)
{
	static t_dir *last_node;
	t_dir *new_node;

	MEM_CHECK((new_node = new_t_dir(name, parent)));
	if (*head == NULL)
		*head = new_node;
	else if (last_node)
		last_node->next = new_node;
	last_node = new_node;
}

void del_t_dirs_recur(t_dir *head)
{
	t_dir *curr;
	t_dir *tmp;

	curr = head;
	while (curr)
	{
		del_t_dirs_recur(curr->content);
		tmp = curr;
		curr = curr->next;
		del_t_dir(&tmp);
	}
}
