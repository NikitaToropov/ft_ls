#include "ft_ls.h"

void 	fill_total(t_dir *node)
{
	t_dir			*curr;
	long int 		sum;

	node->max_width = 1;
	if (node->content)
	{
		sum = 0;
		curr = node->content;
		while (curr)
		{
			sum += (long int)curr->stat.st_blocks;
			if (curr->stat.st_size > node->max_width)
				node->max_width = node->stat.st_size;
			curr = curr->next;
		}
		node->total_size = sum;
	}
	else
		node->total_size = 0;
}

