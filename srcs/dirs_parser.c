#include "ft_ls.h"

char is_dummy_dir(t_dir *node)
{
	if (node->parent)
	{
		if (ft_strcmp(node->name, ".") == 0
			|| ft_strcmp(node->name, "..") == 0)
			return (TRUE);
	}
	return (FALSE);
}

void fill_the_node_content(t_dir *node, unsigned short flags)
{
	DIR *dir;
	struct dirent *dirent;

	if ((flags & get_flag_code('R')) || !(node->parent))
	{
		dirent = NULL;
		dir = NULL;
		if ((dir = opendir(node->path)))
		{
			while ((dirent = readdir(dir)))
				push_back(&(node->content), dirent->d_name, node);
			closedir(dir);
			t_dirs_sorting_by_flags_facade(&(node->content), flags);
			parse_nodes_recursively(&(node->content), node, flags);
		}
		else
			node->status |= PERMISSION_DENIED;
	}
}

char stat_handler(t_dir *node, unsigned short flags)
{
	(void) flags;

	if (lstat(node->path, &(node->stat)) != -1)
	{
		fill_time(node, flags);
		fill_group_name(node, flags);
		fill_sym_link(node, flags);
		fill_file_mod(node, flags);
		fill_owner_name(node, flags);
		node->num_of_links = node->stat.st_nlink;
		node->size_in_bytes = node->stat.st_size;
		node->status |= (S_ISDIR(node->stat.st_mode)) ? DIRECTORY : FILE;
		node->status |= (node->status & DIRECTORY && is_dummy_dir(node))
						? DUMMY_DIR : 0;
		return (SUCCESS);
	}
	else
	{
		node->status = NO_SUCH_FILE_OR_DIR;
		error_handler(NO_SUCH_FILE_OR_DIR, node->name);
		return (FAILURE);
	}
}


void parse_nodes_recursively(t_dir **content_head, t_dir *parent,
							 unsigned short flags)
{
	t_dir *curr;
	t_helper helper;
	size_t tmp_len;

	curr = *content_head;
	ft_bzero(&helper, sizeof(helper));
	while (curr)
	{
		if (stat_handler(curr, flags) == SUCCESS)
		{
			helper.sum_blocks += (long int) curr->stat.st_blocks;
			if (curr->status == DIRECTORY)
				fill_the_node_content(curr, flags);
			if (curr->size_in_bytes > helper.biggest_file_size)
				helper.biggest_file_size = curr->size_in_bytes;
			if ((tmp_len = ft_strlen(curr->owner_name)) > helper.longest_owner)
				helper.longest_owner = tmp_len;
			if ((tmp_len = ft_strlen(curr->group_name)) > helper.longest_group)
				helper.longest_group = tmp_len;
		}
		curr = curr->next;
	}
	fill_total(parent, helper.sum_blocks);
	fill_format(parent, flags, helper);
	t_dirs_sorting_by_flags_facade(content_head, flags);
}

t_dir *dir_parser_facade(char **argv, unsigned short flags)
{
	t_dir *head;

	(void) argv;
	(void) flags;
	head = NULL;
	if (*argv == NULL)
		push_back(&head, ".", NULL);
	else
	{
		while (*argv != NULL)
		{
			push_back(&head, *argv, NULL);
			argv++;
		}
	}
	parse_nodes_recursively(&head, NULL, flags);
	return (head);
}
