#include "ft_ls.h"

void fill_time(t_dir *node, unsigned short flags)
{
	char *full_date;
	time_t current_time;
	time_t *node_time;

	if (flags & get_flag_code('U'))
	{
		node_time = &(node->stat.st_birthtime);
		node->node_sec_time = node->stat.st_birthtimespec.tv_sec;
		node->node_nsec_time = node->stat.st_birthtimespec.tv_nsec;
	}

	else
	{
		node_time = &(node->stat.st_mtime);
		node->node_sec_time = node->stat.st_mtimespec.tv_sec;
		node->node_nsec_time = node->stat.st_mtimespec.tv_nsec;
	}
	full_date = ctime((const time_t *) node_time);
	ft_strncpy(node->date, full_date + 4, 12);
	time(&current_time);
	if ((current_time - *node_time) >= SIX_MONTHS)
		ft_strncpy(node->date + 7, full_date + 19, 5);
}

