#include "ft_ls.h"

int				main(int argc, char **argv)
{
	t_format	format;

	init_format_struct(argc, argv, &format);
	ft_printf("%i\n", format.argc);
	ft_printf("%s", format.argv[0]);
//	parse_params(&format);
	return (0);
}