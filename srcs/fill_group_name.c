#include "ft_ls.h"

void fill_group_name(t_node *node, unsigned short flags)
{
	(void) flags;
	if ((node->group = getgrgid(node->stat.st_gid)))
		node->group_name = node->group->gr_name;
//		node->group_name = ft_strdup(node->group->gr_name);
}
