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
				   ? DUMMY_DIR
				   : node->status;
	if (node->parent)
	{
		node->parent->total_size += node->blocks;
		fill_format(node->parent, flags, node);
	}
	return (node);
}

static void parse_the_dir(t_node *parent, unsigned short flags)
{
	DIR *dir;
	struct dirent *dirent;
	t_node *curr;
	static char printing_mod;

	if (!parent) return;
	if ((dir = opendir(parent->path)))
	{
		while ((dirent = readdir(dir)))
		{
			if (dirent->d_name[0] == '.'
				&& !(flags & get_flag_code('a') || flags & get_flag_code('f')))
				continue;
			curr = stat_handler(new_t_dir(dirent->d_name, parent), flags);
			curr->next = parent->content;
			parent->content = curr;
		}
		closedir(dir);
		nodes_sorting_by_flags(&(parent->content), flags);
		print_dir(parent, flags, printing_mod); // todo fix W-L-BREAK
	}
	else error_handler(PERMISSION_DENIED, parent->name);
	printing_mod = W_LINE_BREAK;
}

void
init_dirs_files_invalids(t_facade *facade, char **argv, unsigned short flags)
{
	t_node *tmp;
	struct stat stt;

	ft_bzero(facade, sizeof(t_facade));
	if (*argv == NULL)
		facade->dirs = stat_handler(new_t_dir(".", NULL), flags);
	while (*argv != NULL)
	{
		if (lstat(*argv, &stt) != -1)
		{
			if (S_ISDIR(stt.st_mode))
			{
				tmp = stat_handler(new_t_dir(*argv, NULL), flags);
				insert_order_by(&(facade->dirs), tmp, flags);
			}
			else
			{
				tmp = stat_handler(new_t_dir(*argv, &(facade->files_parent)),
								   flags);
				insert_order_by(&(facade->files_parent.content), tmp, flags);
			}
		}
		else
		{
			tmp = new_t_dir(*argv, NULL); // TODO check later
			insert_order_by(&(facade->invalid_nodes), tmp,
							0); // todo delete magic number
		}
		argv++;
	}
}

static void
recursive_dir_printing(struct s_node *dirs_head, unsigned short flags)
{
	t_node *tmp;

	tmp = dirs_head;
	while (tmp)
	{
		if (tmp->status == DIRECTORY)
		{
			parse_the_dir(tmp, flags);
			if (tmp->content)
			{
				tmp = tmp->content;
				continue;
			}
		}
		while (!tmp->next && (tmp = tmp->parent))
			del_line_of_nodes(&(tmp->content));
		if (tmp) tmp = tmp->next;
	}
}


static void simple_dir_printing(struct s_node *dirs_head, unsigned short flags)
{
	t_node *tmp;

	tmp = dirs_head;
	while (tmp)
	{
		parse_the_dir(tmp, flags);
		del_line_of_nodes(&(tmp->content));
		tmp = tmp->next;
	}
}

void dir_parser_facade(char **argv, unsigned short flags)
{
	t_facade facade;

	init_dirs_files_invalids(&facade, argv, flags);

	print_invalids(facade.invalid_nodes);

	print_one_column((facade.files_parent).content, flags);

	if (flags & get_flag_code('R'))
		recursive_dir_printing(facade.dirs, flags);
	else
		simple_dir_printing(facade.dirs, flags);

	del_line_of_nodes(&(facade.dirs->content));


	del_line_of_nodes(&(facade.dirs));
	del_line_of_nodes(&((facade.files_parent).content));
}
