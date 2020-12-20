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

static char is_hidden_node(char *name)
{
	return (name[0] == '.') ? TRUE : FALSE;
}

//static void fill_the_dir_content(t_node *parent, unsigned short flags)
//{
//	DIR *dir;
//	struct dirent *dirent;
//
//	if ((flags & get_flag_code('R')) || !(parent->parent))
//	{
//		dirent = NULL;
//		dir = NULL;
//		if ((dir = opendir(parent->path)))
//		{
//			while ((dirent = readdir(dir)))
//			{
//				if (dirent->d_name[0] == '.' && !(flags & get_flag_code('a')))
//					continue;
//				push_back(&(parent->content), dirent->d_name, parent);
//			}
//			closedir(dir);
//			parse_nodes_recursively(&(parent->content), flags);
//		}
//		else
//			parent->status |= PERMISSION_DENIED;
//	}
//}


/**
 * TODO can add dirent->namelen
 */
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
	node->status = (node->status & DIRECTORY && is_dummy_dir(node))
				   ? DUMMY_DIR : 0;
	if (node->parent)
	{
		node->parent->blocks += node->blocks;
		fill_format(node->parent, flags, node);
	}
}

//void parse_nodes_recursively(t_node **content_head, unsigned short flags)
//{
//	t_node *curr;
//	t_node *parent;
//	long int sum_blocks;
//
//	nodes_sorting_by_flags(content_head, flags);
//	curr = *content_head;
//	if (!curr)
//		return;
//	parent = (*content_head)->parent;
//	sum_blocks = 0;
//	while (curr)
//	{
//		stat_handler(curr, flags);
//		fill_format(parent, flags, curr);
//		sum_blocks += (long int) curr->blocks;
//		if (curr->status == DIRECTORY) fill_the_dir_content(curr, flags);
//		curr = curr->next;
//	}
//	if (parent) parent->total_size = sum_blocks;
//}

void parse_the_dir(t_node *parent, unsigned short flags)
{
	DIR *dir;
	struct dirent *dirent;
	t_node *curr;

	if (!parent) return;
	if ((dir = opendir(parent->path)))
	{
		while ((dirent = readdir(dir)))
		{
			if (is_hidden_node(dirent->d_name) &&
				!(flags & get_flag_code('a') || flags & get_flag_code('f')))
				continue;
			curr = new_t_dir(dirent->d_name, parent);
			stat_handler(curr, flags);
			insert_order_by(&(parent->content), curr, flags);
		}
		closedir(dir);
		print_dir_info(parent, flags, W_LINE_BREAK);
	}
	else
		error_handler(PERMISSION_DENIED, parent->name);
}

void dir_parser_facade(char **argv, unsigned short flags)
{
	struct stat stt;
	t_node *dirs_head;
	t_node files_parent;
	t_node *invalid_nodes;
	t_node *tmp;

	ft_bzero(&files_parent, sizeof(t_node));
	dirs_head = NULL;
	invalid_nodes = NULL;
	tmp = NULL;

	if (*argv == NULL)
	{
		dirs_head = new_t_dir(".", NULL);
		stat_handler(dirs_head, flags);
	}
	while (*argv != NULL)
	{
		if (lstat(*argv, &stt) != -1)
		{
			if (S_ISDIR(stt.st_mode))
			{
				tmp = new_t_dir(*argv, NULL);
				stat_handler(tmp, flags);
				insert_order_by(&dirs_head, tmp, flags);
			}
			else
			{
				tmp = new_t_dir(*argv, &files_parent);
				stat_handler(tmp, flags);
				insert_order_by(&(files_parent.content), tmp, flags);
			}
		}
		else
		{
			tmp = new_t_dir(*argv, &files_parent);
			insert_order_by(&invalid_nodes, tmp, 0);
		}
		argv++;
	}

	nodes_sorting_by_flags(&invalid_nodes, 0);
	print_invalids(invalid_nodes);

	parse_the_dir(dirs_head, flags);
	del_line_of_nodes(dirs_head->content);


//	nodes_sorting_by_flags(&dirs_head, flags);

	del_line_of_nodes(dirs_head);
	del_line_of_nodes(files_parent.content);
	del_line_of_nodes(invalid_nodes);



//	if (facade->invalid_nodes)
//		nodes_sorting_by_flags(&(facade->invalid_nodes), 0);
//	if (facade->dirs_head)
//		parse_nodes_recursively(&(facade->dirs_head), flags);
//	if (facade->files_parent.content)
//		parse_nodes_recursively(&(facade->files_parent.content), flags);
}
