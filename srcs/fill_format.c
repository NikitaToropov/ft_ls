#include "ft_ls.h"


size_t width(int num)
{
	if (num >= 100000)
	{
		if (num >= 10000000)
		{
			if (num >= 1000000000) return 10;
			if (num >= 100000000) return 9;
			return 8;
		}
		if (num >= 1000000) return 7;
		return 6;
	}
	else
	{
		if (num >= 1000)
		{
			if (num >= 10000) return 5;
			return 4;
		}
		else
		{
			if (num >= 100) return 3;
			if (num >= 10) return 2;
		}
		return 1;
	}
}

void fill_format(t_node *parent, unsigned short flags, t_node *curr)
{
	size_t len;

	(void) flags;
	if (!parent || !curr)
		return;
	if ((len = width(curr->size_in_bytes)) > parent->format.size_len)
		parent->format.size_len = len;
	if ((len = width(curr->num_of_links)) > parent->format.num_of_links_len)
		parent->format.num_of_links_len = len;
	if ((len = ft_strlen(curr->owner_name)) > parent->format.owner_len)
		parent->format.owner_len = len;
	if ((len = ft_strlen(curr->group_name)) > parent->format.group_len)
		parent->format.group_len = len;
}
