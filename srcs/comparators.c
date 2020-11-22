#include "ft_ls.h"

char compare_by_date(const t_dir *first, const t_dir *second)
{
	if (first->node_time
		> second->node_time)
		return (MORE);
	else
		return (LESS);
}

char compare_by_date_reverse(const t_dir *first, const t_dir *second)
{
	if (first->node_time
		< second->node_time)
		return (LESS);
	else
		return (MORE);
}

char compare_lexicographic(const t_dir *first, const t_dir *second)
{
	if (ft_strcmp(first->name, second->name) > 0)
		return (MORE);
	else
		return (LESS);
}

char compare_lexicographic_reverse(const t_dir *first, const t_dir *second)
{
	if (ft_strcmp(first->name, second->name) > 0)
		return (LESS);
	else
		return (MORE);
}
