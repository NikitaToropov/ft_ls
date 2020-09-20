#include "ft_ls.h"

int			main(int argc, char **argv)
{
	int		format;

	format = parse_flags(argc, argv);
//	run_program(format);
	exit (0);
}