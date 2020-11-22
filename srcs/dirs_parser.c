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

void parse_dir_contents(t_dir *node, unsigned short flags)
{
	DIR *dir;
	struct dirent *dirent;

	(void) flags;
	dirent = NULL;
	if ((dir = opendir(node->path)))
	{
		while ((dirent = readdir(dir)))
			push_back(&(node->content), dirent->d_name, node);
		closedir(dir);
		t_dirs_sorting_by_flags_facade(&(node->content), flags);
		parse_subdir_recursively(&(node->content), flags);
	}
	else
		node->status = PERMISSION_DENIED;
}

char stat_handler(t_dir *node, unsigned short flags)
{
	(void) flags;

	if (lstat(node->path, &(node->stat)) != -1)
	{
		fill_date_string(node, flags);
		fill_group_name(node, flags);
		fill_sym_link(node, flags);
		fill_file_mod(node, flags);
		return (SUCCESS);
	}
	else
	{
		node->status = NO_SUCH_FILE_OR_DIR;
		error_handler(NO_SUCH_FILE_OR_DIR, node->name);
		return (FAILURE);
	}
}


void parse_subdir_recursively(t_dir **head, unsigned short flags)
{
	t_dir *curr;

	curr = *head;
	while (curr)
	{
		if (stat_handler(curr, flags) == SUCCESS)
		{
			if (S_ISDIR(curr->stat.st_mode)
				&& is_dummy_dir(curr) == FALSE)
			{
				if ((flags & get_flag_code('R')) || !(curr->parent))
					parse_dir_contents(curr, flags);
			}
		}
		curr = curr->next;
	}
	t_dirs_sorting_by_flags_facade(head, flags);
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
//		if (!(flags & get_flag_code('f')))
//			head = quick_sort_t_dirs_recur(head, get_tail(head),
//				compare_lexicographic);
	}
	parse_subdir_recursively(&head, flags);
	t_dirs_sorting_by_flags_facade(&head, flags);
	return (head);
}
