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

void dir_handler(t_dir *node, unsigned short flags)
{
	DIR *dir;
	struct dirent *dirent;

	(void) flags;
	dirent = NULL;
	if ((dir = opendir(node->path)))
	{
		while ((dirent = readdir(dir)))
			push_front(&(node->content), dirent->d_name, node);
		closedir(dir);
		sort_list_by(&(node->content), compare_lexicographic);
		parse_format_recur(node->content, flags);
	}
	else
		node->status = PERMISSION_DENIED;
}

char stat_handler(t_dir *node, unsigned short flags)
{
	(void) flags;

	if (lstat(node->path, &(node->stat)) != -1)
	{
		return (SUCCESS);
	}
	else
	{
		node->status = NO_SUCH_FILE_OR_DIR;
		error_handler(NO_SUCH_FILE_OR_DIR, node->name);
		return (FAILURE);
	}
}


void parse_format_recur(t_dir *head, unsigned short flags)
{
	t_dir *curr;

	curr = head;
	while (curr)
	{
		if (stat_handler(curr, flags) == SUCCESS)
			if (S_ISDIR(curr->stat.st_mode)
				&& is_dummy_dir(curr) == FALSE)
			{
				if ((flags & get_flag_code('R')) || !(curr->parent))
					dir_handler(curr, flags);
			}
		curr = curr->next;
	}
}

t_dir *dirs_parser(char **argv, unsigned short flags)
{
	t_dir *head;

	(void) argv;
	(void) flags;
	head = NULL;
	if (*argv == NULL)
		push_front(&head, ".", NULL);
	else
	{
		while (*argv != NULL)
		{
			push_front(&head, *argv, NULL);
			argv++;
		}
		sort_list_by(&head, compare_lexicographic);
	}
	parse_format_recur(head, flags);
	return (head);
}
