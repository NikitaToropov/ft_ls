#include "ft_ls.h"

void print_dir(t_dir *dir, unsigned short flags)
{
	(void) flags;
	ft_printf("%s\n", dir->name);
}

void print_dirs_struct_recur(t_dir *head, unsigned short flags)
{
	t_dir *curr;

	(void) flags;
	curr = head;
	while(curr)
	{
		print_dir(curr, flags);
		curr = curr->next;
	}
	curr = head;
	while(curr)
	{
		if (S_ISDIR(curr->stat.st_mode)
			&& is_dummy_dir(curr) == FALSE)
		{
			ft_printf("\n%s:\ntotal %ui\n", curr->path, curr->stat.st_blocks);
			print_dirs_struct_recur(curr->content, flags);
		}
		curr = curr->next;
	}
}

void print_dirs_struct(t_dir *head, unsigned short flags)
{
	t_dir *node;

	node = head;
	if (node->next == NULL)
	{
		if (S_ISDIR(node->stat.st_mode))
			ft_printf("total %i\n", node->stat.st_blocks);
		else if (node->status == 0)
		{
			print_dir(node, flags);
			ft_printf("\n");
		}
		print_dirs_struct_recur(node->content, flags);
	} else
	{
		while(node)
		{
			if (S_ISDIR(node->stat.st_mode))
			{
				ft_printf("%s:\ntotal %i\n", node->path, node->stat.st_blocks);
				print_dirs_struct_recur(node->content, flags);
			} else if (node->status == 0)
			{
				print_dir(node, flags);
				ft_printf("\n");
			}
			node = node->next;
		}
	}
}
