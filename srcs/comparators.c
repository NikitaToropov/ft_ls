/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comparators.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmissy <cmissy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 15:28:25 by cmissy            #+#    #+#             */
/*   Updated: 2021/01/10 15:35:03 by cmissy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	compare_by_date(const t_node *first, const t_node *second)
{
	if (first->node_sec_time > second->node_sec_time)
		return (LESS);
	else if (first->node_sec_time == second->node_sec_time)
	{
		if (first->node_nsec_time >= second->node_nsec_time)
			return (LESS);
		else
			return (MORE);
	}
	else
		return (MORE);
}

char	compare_by_date_reverse(const t_node *first, const t_node *second)
{
	if (compare_by_date(first, second) == LESS)
		return (MORE);
	else
		return (LESS);
}

char	compare_lexicographic(const t_node *first, const t_node *second)
{
	if (ft_strcmp(first->name, second->name) > 0)
		return (MORE);
	else
		return (LESS);
}

char	compare_lexicographic_reverse(const t_node *first, const t_node *second)
{
	if (ft_strcmp(first->name, second->name) > 0)
		return (LESS);
	else
		return (MORE);
}

char	default_for_pushing_back(const t_node *first, const t_node *second)
{
	(void)first;
	(void)second;
	return (LESS);
}
