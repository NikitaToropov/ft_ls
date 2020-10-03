#include "ft_ls.h"

t_dir *new_t_dir(char *name)
{
	t_dir	*new;

//	if (!valid_name)
		new = NULL;
//	else
//	{
		MEMCHECK((new = ft_memalloc(sizeof(t_dir))));
		new->name = name;
//	}
	return (new);
}
