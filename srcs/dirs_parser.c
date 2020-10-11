#include "ft_ls.h"

t_dir *dirs_parser(char **argv, unsigned short flags)
{
	t_dir *head;

	(void)argv;
	(void)flags;
	head = NULL;
	if (*argv == NULL)
		push_front(&head, ft_strdup("."));
	else
	{
		while (*argv != NULL)
		{
			push_front(&head, ft_strdup(*argv));
			argv++;
		}
	}
	sort_list_by(&head, compare_lexicographic);
	return (head);
}
