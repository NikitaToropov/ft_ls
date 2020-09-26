#include "ft_ls.h"

void			init_format_struct(int argc, char **argv, t_format *format)
{
	format->files_or_dirs = NULL;
	format->num_of_files_or_dirs = 0;
	format->flags = 0;
	format->argc = (size_t)(argc - 1);
	format->argv = &argv[1];
}