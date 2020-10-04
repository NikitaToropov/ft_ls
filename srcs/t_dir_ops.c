#include "ft_ls.h"

char compare_by_date(const t_dir *first, const t_dir *second,
		unsigned short flags)
{
	if (first->description.date.unix_time
		> second->description.date.unix_time)
	{
		if (flags & get_flag_code('r'))
			return (LESS);
		return (MORE);
	}
	else
	{
		if (flags & get_flag_code('r'))
			return (MORE);
		return (LESS);
	}
}

void t_dir_quick_sort(t_dir **root, unsigned short flags,
		char compare_by(const t_dir *, const t_dir *, unsigned short))
{
	compare_by(*root, (*root)->next, flags);
	return;
}

t_dir *new_t_dir(char *name)
{
	t_dir *new;

	MEMCHECK((new = ft_memalloc(sizeof(t_dir))));
	new->name = name;
	return (new);
}
