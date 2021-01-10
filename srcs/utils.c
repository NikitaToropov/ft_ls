/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmissy <cmissy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 13:16:23 by cmissy            #+#    #+#             */
/*   Updated: 2021/01/10 13:16:23 by cmissy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char		is_dummy_dir(t_node *node)
{
	if (node->parent)
	{
		if (ft_strcmp(node->name, ".") == 0
			|| ft_strcmp(node->name, "..") == 0)
			return (TRUE);
	}
	return (FALSE);
}

char		*ft_pathjoin(char *first, char *second)
{
	size_t	i;
	char	*new;

	if (!first)
		return (ft_strdup(second));
	MEM_CHECK((new = malloc(ft_strlen(first) + ft_strlen(second) + 2)));
	i = 0;
	while (*first)
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
