#include "ft_ls.h"

void print_dir_description(t_node *dir, unsigned short flags)
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

void print_content(t_node *node, unsigned short flags)
{
	t_dir_format format;
	char *format_string;

	if (node->status == NO_SUCH_FILE_OR_DIR) return;
	if (node->parent) format = node->parent->format;
	else ft_bzero(&format, sizeof(format));
	if (flags & get_flag_code('g')) format_string = G_FORMATTING;
	else if (flags & get_flag_code('l')) format_string = L_FORMATTING;
	else format_string = L_FORMATTING;
	ft_printf(format_string,
			  node->file_mod,
			  format.num_of_links_len,
			  node->num_of_links,
			  format.owner_len,
			  node->owner_name,
			  format.group_len,
			  node->group_name,
			  format.size_len,
			  node->size_in_bytes,
			  node->date,
			  node->name,
			  (node->sym_link != NULL) ? node->sym_link : "");
}

void print_dirs_struct_recur(t_node *head, unsigned short flags)
{
	t_node *curr;

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

void print_dirs_struct(t_node *head, unsigned short flags)
{
	t_node *node;

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
