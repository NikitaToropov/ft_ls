#include "ft_ls.h"

int main(int argc, char **argv)
{
	unsigned short flags;
//	t_dirs *dirs;

	(void)argc;
	flags = flags_parser(argv);
	ft_printf("%bi", flags);
//	dirs_parser(argv);

	return (0);
}
