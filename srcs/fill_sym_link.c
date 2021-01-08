/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_sym_link.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmissy <cmissy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 16:28:03 by cmissy            #+#    #+#             */
/*   Updated: 2021/01/08 16:29:10 by cmissy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		fill_sym_link(t_node *node, struct stat stt)
{
	ssize_t	buffsize;
	ssize_t	real_size;
	char	*link;

	link = NULL;
	if ((buffsize = DEFAULT_BUFF_SIZE) < 16)
		exit(1);
	if (S_ISLNK(stt.st_mode))
	{
		MEM_CHECK((link = malloc(buffsize)));
		while ((real_size = readlink(node->path, link, buffsize)) >= buffsize
				&& real_size != -1)
		{
			buffsize <<= 1;
			free(link);
			MEM_CHECK((link = malloc(buffsize)));
		}
		if (real_size == -1)
			return ;
		link[real_size] = '\0';
		node->sym_link = ft_strjoin(SYM_LINK_ARROW, link);
		free(link);
	}
}
