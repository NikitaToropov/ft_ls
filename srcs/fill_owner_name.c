#include "ft_ls.h"

void fill_owner_name(t_dir *node, unsigned short flags)
{
	(void) flags;
	node->passwd = getpwuid(node->stat.st_uid);
}
