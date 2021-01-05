#include "ft_ls.h"

int main(int argc, char **argv)
{
	unsigned short flags;

	(void) argc;
	flags = flags_parser_facade(&argv);
	dir_parser_facade(argv, flags);
	return (0);
}
