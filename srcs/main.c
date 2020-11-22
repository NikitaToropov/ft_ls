#include "ft_ls.h"

int main(int argc, char **argv)
{
	unsigned short flags;
	t_dir *head;

	(void) argc;
	flags = flags_parser_facade(&argv);
	head = dir_parser_facade(argv, flags);
	print_dirs_struct(head, flags);
	del_t_dirs_recur(head);
	return (0);
}
