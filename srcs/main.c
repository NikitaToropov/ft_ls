#include "ft_ls.h"

int main(int argc, char **argv)
{
	unsigned short flags;
	t_dir *head;
//	DIR *for_freeing;

	(void)argc;
	flags = flags_parser(&argv);
	head = dirs_parser(argv, flags);
	ft_printf("%bi\nstring after flags = %s\n", flags, *argv);
//	if ((for_freeing = opendir(*argv)) == NULL)
//		ft_printf("NULL");
//	else
//		closedir(for_freeing);
	del_t_dirs_recur(&head);
	while (head)
	{
		ft_printf("%s\n", head->name);
		head = head->next;
	}
	return (0);
}
