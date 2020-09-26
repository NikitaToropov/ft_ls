#include "ft_ls.h"

int			parse_flags(int argc, char **argv)
{
	if (argv)
		return (1);
	else if (argc > 1)
		return (2);
	return (12);
}