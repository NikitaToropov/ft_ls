#include "ft_ls.h"

void print_dir_description(t_dir *dir, unsigned short flags)
{
	(void) flags;
	ft_printf("\n%s:\n%li\n", dir->path, dir->stat.st_blocks);
}

void print_content(t_dir *node, unsigned short flags)
{
	fill_date_string(node, flags);
	fill_group_name(node, flags);
	fill_owner_name(node, flags);
	ft_printf("%s %s %7u %s %s\n", node->passwd->pw_name, node->group_info->gr_name, node->stat.st_size, node->date, node->name);
}

void print_dirs_struct_recur(t_dir *head, unsigned short flags)
{
	t_dir *curr;

	(void) flags;
	curr = head;
	while(curr)
	{
		print_content(curr, flags);
		curr = curr->next;
	}
	curr = head;
	while(curr)
	{
		if (S_ISDIR(curr->stat.st_mode)
			&& is_dummy_dir(curr) == FALSE)
		{
			print_dir_description(curr, flags);
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
			ft_printf("total %i\n", node->total_size);
		else if (node->status == 0)
		{
			print_content(node, flags);
			ft_printf("\n");
		}
		print_dirs_struct_recur(node->content, flags);
	}
	else
	{
		while(node)
		{
			if (S_ISDIR(node->stat.st_mode))
			{
				print_dir_description(node, flags);
				print_dirs_struct_recur(node->content, flags);
			}
			else if (node->status == 0)
			{
				print_content(node, flags);
			}
			node = node->next;
		}
	}
}
