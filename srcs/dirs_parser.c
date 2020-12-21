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

/**
 * TODO can add dirent->namelen
 */
static t_node *stat_handler(t_node *node, unsigned short flags)
{
	struct passwd *passwd;
	struct stat stat;

	lstat(node->path, &(stat));
	fill_time(node, flags, stat);
	node->group_name = getgrgid(stat.st_gid)->gr_name;
	fill_sym_link(node, flags, stat);
	fill_file_mod(node, flags, stat);
	node->owner_name = ((passwd = getpwuid(stat.st_uid)))
					   ? ft_strdup(passwd->pw_name)
					   : ft_itoa(stat.st_uid);
	node->blocks = stat.st_blocks;
	node->num_of_links = stat.st_nlink;
	node->size_in_bytes = stat.st_size;
	node->status |= (S_ISDIR(stat.st_mode)) ? DIRECTORY : FILE;
	node->status = (node->status & DIRECTORY && is_dummy_dir(node))
				   ? DUMMY_DIR : node->status;
	if (node->parent)
	{
		node->parent->total_size += node->blocks;
		fill_format(node->parent, flags, node);
	}
	return (node);
}

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
			curr = stat_handler(new_t_dir(dirent->d_name, parent), flags);
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
		dirs_head = stat_handler(new_t_dir(".", NULL), flags);
	while (*argv != NULL)
	{
		if (lstat(*argv, &stt) != -1)
		{
			if (S_ISDIR(stt.st_mode))
			{
				tmp = stat_handler(new_t_dir(*argv, NULL), flags);
				insert_order_by(&dirs_head, tmp, flags);
			}
			else
			{
				tmp = stat_handler(new_t_dir(*argv, &files_parent), flags);
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

	/**
	 * TODO need add print_by_columns
	 */
//	nodes_sorting_by_flags(&invalid_nodes, 0);
	print_invalids(invalid_nodes);
	print_one_column(files_parent.content, flags);

	parse_the_dir(dirs_head, flags);
	del_line_of_nodes(&(dirs_head->content));


//	nodes_sorting_by_flags(&dirs_head, flags);

	del_line_of_nodes(&(dirs_head));
	del_line_of_nodes(&(files_parent.content));
//	del_line_of_nodes(&(invalid_nodes));



//	if (facade->invalid_nodes)
//		nodes_sorting_by_flags(&(facade->invalid_nodes), 0);
//	if (facade->dirs_head)
//		parse_nodes_recursively(&(facade->dirs_head), flags);
//	if (facade->files_parent.content)
//		parse_nodes_recursively(&(facade->files_parent.content), flags);
}
