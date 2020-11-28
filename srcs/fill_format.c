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

void fill_format(t_dir *node, unsigned short flags, t_helper helper)
{
	(void) flags;
	if (!node)
		return;
	node->format.owner_len = helper.longest_owner;
	node->format.group_len = helper.longest_group;
	node->format.size_len = width((int)helper.biggest_file_size);
}
