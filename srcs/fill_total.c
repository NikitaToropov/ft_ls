#include "ft_ls.h"

//static int	get_blocksize()
//{
//	const char		*blocksizestr;
//	int				blocksize;
//
//	blocksizestr = getenv("BLOCKSIZE");
//	if (blocksizestr == NULL)
//	{
//		exit(0); // TO DO: error handle
//	}
//	blocksize = ft_atoi(blocksizestr);
//	return (blocksize);
//}

void 	fill_total(t_dir *node)
{
	t_dir			*curr;
	long int 		sum;

	curr->max_width = 1;
	if (node->content)
	{
		sum = 0;
		curr = node->content;
		while (curr)
		{
			sum += (long int)((curr->stat.st_size * curr->stat.st_blksize) / curr->stat.st_blocks);
			if (curr->stat.st_size > curr->max_width)
				curr->max_width = curr->stat.st_size;
			curr = curr->next;
		}
		curr->total_size = sum;
	}
	else
		curr->total_size = 0;
}

