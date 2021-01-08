/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_time.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmissy <cmissy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 16:33:02 by cmissy            #+#    #+#             */
/*   Updated: 2021/01/08 17:51:42 by enikole          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		fill_time(t_node *node, unsigned short flags, struct stat stt)
{
	char	*full_date;
	time_t	current_sec_time;

	if (flags & get_flag_code('U'))
	{
		node->node_sec_time = stt.st_birthtimespec.tv_sec;
		node->node_nsec_time = stt.st_birthtimespec.tv_nsec;
	}
	else if (flags & get_flag_code('u'))
	{
		node->node_sec_time = stt.st_atimespec.tv_sec;
		node->node_nsec_time = stt.st_atimespec.tv_nsec;
	}
	else
	{
		node->node_sec_time = stt.st_mtimespec.tv_sec;
		node->node_nsec_time = stt.st_mtimespec.tv_nsec;
	}
	full_date = ctime((const time_t *)&(node->node_sec_time));
	ft_strncpy(node->date, full_date + 4, 12);
	time(&current_sec_time);
	if ((current_sec_time - node->node_sec_time) >= SIX_MONTHS)
		ft_strncpy(node->date + 7, full_date + 19, 5);
}
