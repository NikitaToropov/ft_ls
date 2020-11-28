#include "ft_ls.h"

void fill_owner_name(t_dir *node, unsigned short flags)
{

	(void) flags;
	if ((node->passwd = getpwuid(node->stat.st_uid)))
		node->owner_name = ft_strdup(node->passwd->pw_name);
}
