#include "ft_ls.h"

int main(int argc, char **argv)
{
	unsigned short flags;
//	t_dir *dirs;

	(void)argc;
	flags = flags_parser(&argv);
//	dirs = dirs_parser(argv, flags);
	ft_printf("%bi\nstring after flags = %s\n", flags, *argv);
	if (opendir(*argv) == NULL)
		ft_printf("NULL");

	return (0);
}
