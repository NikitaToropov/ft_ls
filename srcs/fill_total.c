#include "ft_ls.h"

void 	fill_total(t_dir *node)
{
	t_dir			*curr;
	long int 		sum_blocks;

	node->max_size = 1;
	if (node->content)
	{
		sum_blocks = 0;
		curr = node->content;
		while (curr)
		{
			sum_blocks += (long int)curr->stat.st_blocks;
			if (curr->stat.st_size > node->max_size)
				node->max_size = curr->stat.st_size;
			curr = curr->next;
		}
		node->total_size = sum_blocks;
	}
	else
		node->total_size = 0;
}

