#include "ft_ls.h"

void fill_group_name(t_dir *node, unsigned short flags)
{
	(void) flags;
	node->group_info = getgrgid(node->stat.st_gid);
}
