#include "ft_ls.h"

char *ft_pathjoin(char *first, char *second)
{
	size_t i;
	char *new;

	if (!first)
		return (ft_strdup(second));
	MEM_CHECK((new = malloc(ft_strlen(first) + ft_strlen(second) + 2)));
	i = 0;
	while(*first)
	{
		new[i++] = *first;
		first++;
	}
	new[i++] = '/';
	while (*second)
	{
		new[i++] = *second;
		second++;
	}
	new[i] = '\0';
	return (new);
}
