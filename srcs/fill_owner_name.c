#include "ft_ls.h"

void fill_owner_name(t_node *node, unsigned short flags)
{

		(void) flags;
	if ((node->passwd = getpwuid(node->stat.st_uid)))
		node->owner_name = ft_strdup(node->passwd->pw_name);
	else
		node->owner_name = ft_itoa(node->stat.st_uid);
}
