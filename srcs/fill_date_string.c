#include "ft_ls.h"

void fill_date_string(t_dir *node, unsigned short flags)
{
	char *full_date;
	time_t current_time;
	time_t *node_time;

	if (flags & get_flag_code('U'))
		node_time = &(node->stat.st_birthtime);
	else
		node_time = &(node->stat.st_mtime);
	full_date = ctime((const time_t *) node_time);
	ft_strncpy(node->date, full_date + 4, 12);
	time(&current_time);
	if ((current_time - *node_time) >= SIX_MONTHS)
		ft_strncpy(node->date + 7, full_date + 19, 5);
	node->node_time = *node_time;
}

