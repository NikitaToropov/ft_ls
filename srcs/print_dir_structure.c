#include "ft_ls.h"

void print_dir_description(t_dir *dir, unsigned short flags)
{
	(void) flags;
	ft_printf("\n%s:\n", dir->path);
	if (dir->status == PERMISSION_DENIED)
	{
		error_handler(PERMISSION_DENIED, dir->name);
		return;
	}
//	fill_total(dir);
	ft_printf("total %lli\n", dir->total_size);
}

void print_content(t_dir *node, unsigned short flags)
{
	(void) flags;
	if (node->status == NO_SUCH_FILE_OR_DIR)
		return;
	fill_owner_name(node, flags);
//	ft_printf("%s %u %s %s %7lli %s %s%s",
	ft_printf("%s %u %s %s %7lli %s %s%s\n",
			  node->file_mod,
			  node->stat.st_nlink,
			  node->passwd->pw_name,
			  node->group_info->gr_name,
			  node->stat.st_size,
			  node->date,
			  node->name,
			  (node->sym_link != NULL) ? node->sym_link : "");
//	ft_printf("  %li  %li\n", node->node_sec_time, node->node_nsec_time);
}

void print_dirs_struct_recur(t_dir *head, unsigned short flags)
{
	t_dir *curr;

	(void) flags;
	curr = head;

	while (curr)
	{
		print_content(curr, flags);
		curr = curr->next;
	}
	if (!(flags & get_flag_code('R'))
		&& head
		&& head->parent
		&& !head->parent->parent)
		return;
	curr = head;
	while (curr)
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
	while (node)
	{
		if (S_ISDIR(node->stat.st_mode))
		{
			print_dir_description(node, flags);
			print_dirs_struct_recur(node->content, flags);
		}
		else if (!node->status)
		{
			print_content(node, flags);
		}
		node = node->next;
	}
}
