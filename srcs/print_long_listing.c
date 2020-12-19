#include "ft_ls.h"

void print_long_listing(t_node *node, unsigned short flags)
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

void print_one_column(t_node *head, unsigned short flags)
{
	t_node *curr;

	curr = head;
	while (curr)
	{
		print_long_listing(curr, flags);
		curr = curr->next;
	}
}