#include "ft_ls.h"

char dir_handler (t_dir *node, unsigned short flags)
{
	DIR *dir;

	(void)flags;
		if ((dir = opendir(node->path)) == NULL)
		return (FAILURE);
	closedir(dir);
	return (SUCCESS);
}

char file_handler(t_dir *node, unsigned short flags)
{
	(void)flags;
	(void)node;
	return (SUCCESS);
}

void fill_curr(t_dir *node, unsigned short flags)
{
	if (dir_handler(node, flags) == SUCCESS
	|| file_handler(node, flags) == SUCCESS)
		return;
	node->status = WRONG_NAME;
	error_handler(NO_SUCH_FILE_OR_DIR, node->name);
}

void fill_format(t_dir *head, unsigned short flags)
{
	t_dir *curr;

	curr = head;
	while (curr)
	{
		fill_curr(curr, flags);
		curr = curr->next;
	}
}

t_dir *dirs_parser(char **argv, unsigned short flags)
{
	t_dir *head;

	(void)argv;
	(void)flags;
	head = NULL;
	if (*argv == NULL)
		push_front(&head, ft_strdup("."), NULL);
	else
	{
		while (*argv != NULL)
		{
			push_front(&head, *argv, NULL);
			argv++;
		}
		sort_list_by(&head, compare_lexicographic);
	}
//	fill_format(head, flags);
	return (head);
}
