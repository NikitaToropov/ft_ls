#include "ft_ls.h"

void fill_sym_link(t_dir *node, unsigned short flags)
{
	ssize_t buffsize;
	ssize_t real_size;
	char *link;

	(void) flags;
	link = NULL;
	buffsize = DEFAULT_BUFF_SIZE;
	if (S_ISLNK(node->stat.st_mode))
	{
		MEMCHECK((link = malloc(buffsize)));
		while ((real_size = readlink(node->path, link, buffsize)) >= buffsize
			   && real_size != -1)
		{
			buffsize <<= 1;
			free(link);
			MEMCHECK((link = malloc(buffsize)));
		}
		if (real_size == -1)
			return;
		link[real_size] = '\0';
		node->sym_link = ft_strjoin(SYM_LINK_ARROW, link);
		free(link);
	}
}