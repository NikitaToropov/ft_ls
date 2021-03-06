/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_format.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmissy <cmissy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 15:43:31 by cmissy            #+#    #+#             */
/*   Updated: 2021/01/10 13:09:26 by cmissy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static size_t	less_than_a_hundred_thousand(int num)
{
	if (num >= 1000)
	{
		if (num >= 10000)
			return (5);
		return (4);
	}
	else
	{
		if (num >= 100)
			return (3);
		if (num >= 10)
			return (2);
	}
	return (1);
}

static size_t	more_than_or_equal_to_one_hundred_thousand(int num)
{
	if (num >= 10000000)
	{
		if (num >= 1000000000)
			return (10);
		if (num >= 100000000)
			return (9);
		return (8);
	}
	if (num >= 1000000)
		return (7);
	return (6);
}

static size_t	width(int num)
{
	if (num >= 100000)
		return (more_than_or_equal_to_one_hundred_thousand(num));
	else
		return (less_than_a_hundred_thousand(num));
}

void			fill_format(t_node *parent, t_node *curr)
{
	size_t		len;

	if (!parent || !curr)
		return ;
	parent->format.num_of_files++;
	if ((len = width(curr->size_in_bytes)) > parent->format.size_len)
		parent->format.size_len = len;
	if ((len = width(curr->num_of_links)) > parent->format.num_of_links_len)
		parent->format.num_of_links_len = len;
	if ((len = ft_strlen(curr->owner_name)) > parent->format.owner_len)
		parent->format.owner_len = len;
	if ((len = ft_strlen(curr->group_name)) > parent->format.group_len)
		parent->format.group_len = len;
	if ((len = ft_strlen(curr->name)) > parent->format.name_len)
		parent->format.name_len = len;
}
