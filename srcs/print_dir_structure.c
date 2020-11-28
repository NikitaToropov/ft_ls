#include "ft_ls.h"

void print_dir_description(t_dir *dir, unsigned short flags)
{
	(void) flags;
	ft_printf("\n%s:\n", dir->path);
	if (dir->status & PERMISSION_DENIED)
	{
		error_handler(PERMISSION_DENIED, dir->name);
		return;
	}
	ft_printf("total %lli\n", dir->total_size);
}

void print_content(t_dir *node, unsigned short flags)
{
	(void) flags;
	if (node->status == NO_SUCH_FILE_OR_DIR)
		return;
	ft_printf("%s %u %s %s %7lli %s %s%s\n",
			  node->file_mod,
			  node->num_of_links,
			  node->owner_name,
			  node->group_name,
			  node->size_in_bytes,
			  node->date,
			  node->name,
			  (node->sym_link != NULL) ? node->sym_link : "");

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
		if (curr->status & DIRECTORY
			&& !(curr->status & DUMMY_DIR))
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
		if (node->status & DIRECTORY)
		{
			print_dir_description(node, flags);
			print_dirs_struct_recur(node->content, flags);
		}
		else if (node->status & FILE)
		{
			print_content(node, flags);
		}
		node = node->next;
	}
}
