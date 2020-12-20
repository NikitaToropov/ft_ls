#include "ft_ls.h"

static char is_dummy_dir(t_node *node)
{
	if (node->parent)
	{
		if (ft_strcmp(node->name, ".") == 0
			|| ft_strcmp(node->name, "..") == 0)
			return (TRUE);
	}
	return (FALSE);
}

static void fill_the_dir_content(t_node *parent, unsigned short flags)
{
	DIR *dir;
	struct dirent *dirent;

	if ((flags & get_flag_code('R')) || !(parent->parent))
	{
		dirent = NULL;
		dir = NULL;
		if ((dir = opendir(parent->path)))
		{
			while ((dirent = readdir(dir)))
			{
				if (dirent->d_name[0] == '.' && !(flags & get_flag_code('a')))
					continue;
				push_back(&(parent->content), dirent->d_name, parent);
			}
			closedir(dir);
			parse_nodes_recursively(&(parent->content), flags);
		}
		else
			parent->status |= PERMISSION_DENIED;
	}
}

static void stat_handler(t_node *node, unsigned short flags)
{
	lstat(node->path, &(node->stat));
	fill_time(node, flags);
	fill_group_name(node, flags);
	fill_sym_link(node, flags);
	fill_file_mod(node, flags);
	fill_owner_name(node, flags);
	node->blocks = node->stat.st_blocks;
	node->num_of_links = node->stat.st_nlink;
	node->size_in_bytes = node->stat.st_size;
	node->status |= (S_ISDIR(node->stat.st_mode)) ? DIRECTORY : FILE;
	node->status |= (node->status & DIRECTORY && is_dummy_dir(node))
					? DUMMY_DIR : 0;
}


void parse_nodes_recursively(t_node **content_head, unsigned short flags)
{
	t_node *curr;
	t_node *parent;
	long int sum_blocks;

	nodes_sorting_by_flags(content_head, flags);
	curr = *content_head;
	if (!curr)
		return;
	parent = (*content_head)->parent;
	sum_blocks = 0;
	while (curr)
	{
		stat_handler(curr, flags);
		fill_format(parent, flags, curr);
		sum_blocks += (long int) curr->blocks;
		if (curr->status == DIRECTORY) fill_the_dir_content(curr, flags);
		curr = curr->next;
	}
	if (parent) parent->total_size = sum_blocks;
}

void dir_parser_facade(t_facade *facade, char **argv, unsigned short flags)
{
	struct stat stt;

	if (*argv == NULL)
		push_back(&(facade->dirs), ".", NULL);
	while (*argv != NULL)
	{
		if (lstat(*argv, &stt) != -1)
		{
			if (S_ISDIR(stt.st_mode))
				push_back(&(facade->dirs), *argv, NULL);
			else
				push_back(&(facade->files_parent.content), *argv,
						  &(facade->files_parent));
		}
		else
			push_back(&(facade->invalid_nodes), *argv, NULL);
		argv++;
	}
	if (facade->invalid_nodes)
		nodes_sorting_by_flags(&(facade->invalid_nodes), 0);
	if (facade->dirs)
		parse_nodes_recursively(&(facade->dirs), flags);
	if (facade->files_parent.content)
		parse_nodes_recursively(&(facade->files_parent.content), flags);
}
