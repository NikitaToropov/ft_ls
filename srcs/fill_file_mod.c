#include "ft_ls.h"

void fill_file_mod(t_dir *node, unsigned short flags)
{
	(void) flags;
	node->file_mod[0] = S_ISDIR(node->stat.st_mode) ? 'd' : '-';
	node->file_mod[0] = S_ISLNK(node->stat.st_mode) ? 'l' : node->file_mod[0];
	node->file_mod[1] = (node->stat.st_mode & S_IRUSR) ? 'r' : '-';
	node->file_mod[2] = (node->stat.st_mode & S_IWUSR) ? 'w' : '-';
	node->file_mod[3] = (node->stat.st_mode & S_IXUSR) ? 'x' : '-';
	node->file_mod[4] = (node->stat.st_mode & S_IRGRP) ? 'r' : '-';
	node->file_mod[5] = (node->stat.st_mode & S_IWGRP) ? 'w' : '-';
	node->file_mod[6] = (node->stat.st_mode & S_IXGRP) ? 'x' : '-';
	node->file_mod[7] = (node->stat.st_mode & S_IROTH) ? 'r' : '-';
	node->file_mod[8] = (node->stat.st_mode & S_IWOTH) ? 'w' : '-';
	node->file_mod[9] = (node->stat.st_mode & S_IXOTH) ? 'x' : '-';
}
