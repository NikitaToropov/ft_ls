#include "ft_ls.h"

int main(int argc, char **argv)
{
	unsigned short flags;

	(void) argc;
	flags = flags_parser_facade(&argv);
	dir_parser_facade(argv, flags);
//	print_dirs_struct(facade, flags);
//	del_nodes_recur(facade.dirs);
//	del_nodes_recur(facade.files_parent.content);
//	del_nodes_recur(facade.invalid_nodes);
	return (0);
}
