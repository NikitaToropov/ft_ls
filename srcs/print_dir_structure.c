#include "ft_ls.h"

void print_dir(t_node *parent, unsigned short flags, char printing_mod)
{
//	char *format_string;

	if (!parent || parent->status & DUMMY_DIR || parent->status & DUMMY_DIR)
		return;
	if (parent->path)
	{
		if (printing_mod != WO_DIR_DESCRIPTION)
		{
			if (printing_mod == W_LINE_BREAK)
				ft_printf("\n");
			ft_printf("%s:\n", parent->path);
			if (parent->status & PERMISSION_DENIED)
			{
				error_handler(PERMISSION_DENIED, parent->name);
				return;
			}
		}
		if (parent->content && (flags & get_flag_code('g') || flags & get_flag_code('l')))
			ft_printf("total %li\n", parent->total_size);
	}

}

void
print_dirs_struct_recur(t_node *parent, unsigned short flags, char printing_mod)
{
	t_node *curr;

	if (!parent || (parent->parent && !(flags & get_flag_code('R'))))
		return;
	print_dir(parent, flags, printing_mod);
//	if (flags & get_flag_code('l') || flags & get_flag_code('g'))
//		print_one_column(parent, flags);
//	else
//		print_by_columns(parent->parent);
//	if (!(flags & get_flag_code('R'))
//		&& parent->parent
//		&& !parent->parent->parent)
//		return;
	curr = parent->content;
	while (curr)
	{
		if (curr->status & DIRECTORY && !(curr->status & DUMMY_DIR))
		{
			print_dirs_struct_recur(curr, flags, W_LINE_BREAK);
		}
		curr = curr->next;
	}
}

void print_invalids(t_node *head)
{
	t_node *curr;

	curr = head;
	while (curr)
	{
		error_handler(NO_SUCH_FILE_OR_DIR, curr->name);
		curr = curr->next;
	}
}

void print_dirs_struct(t_facade facade, unsigned short flags)
{
	t_node *node;
	char dir_printing_mode;

	if (facade.files_parent.content)
		dir_printing_mode = W_LINE_BREAK;
	else if ((facade.dirs && facade.dirs->next) || facade.invalid_nodes)
		dir_printing_mode = WO_LINE_BREAK;
	else
		dir_printing_mode = WO_DIR_DESCRIPTION;
	if (facade.files_parent.content)
		print_dirs_struct_recur(&(facade.files_parent), flags,
								dir_printing_mode);
	if (facade.invalid_nodes)
		print_invalids(facade.invalid_nodes);
	node = facade.dirs;
	while (node)
	{
		print_dirs_struct_recur(node, flags, dir_printing_mode);
		dir_printing_mode = W_LINE_BREAK;
		node = node->next;
	}
}
