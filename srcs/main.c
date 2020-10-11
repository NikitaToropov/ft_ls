#include "ft_ls.h"

int main(int argc, char **argv)
{
	unsigned short flags;
	t_dir *head;
	t_dir *tmp;
//	DIR *for_freeing;

	(void)argc;
	flags = flags_parser(&argv);
	head = dirs_parser(argv, flags);
	ft_printf("%bi\nstring after flags = %s\n", flags, *argv);
//	if ((for_freeing = opendir(*argv)) == NULL)
//		ft_printf("NULL");
//	else
//		closedir(for_freeing);
	tmp = head;
	while (tmp)
	{
		ft_printf("%s\n", tmp->path);
		tmp = tmp->next;
	}
	del_t_dirs_recur(&head);
	DIR *first_dir = opendir("srcs");
	DIR *second_dir = opendir("include");

	if (first_dir)
		ft_printf("\n\nSRCS FD %d\n", first_dir->__dd_fd);
	if (second_dir)
		ft_printf("\n\nINCL FD %d\n", second_dir->__dd_fd);

	return (0);
}
