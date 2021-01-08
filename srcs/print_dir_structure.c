/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_dir_structure.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmissy <cmissy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 16:41:27 by cmissy            #+#    #+#             */
/*   Updated: 2021/01/08 16:42:52 by cmissy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		print_dir(t_node *parent, unsigned short flags, char *printing_mod)
{
	if (parent->status == DUMMY_DIR)
		return ;
	if (parent->path)
	{
		if (*printing_mod != WO_DIR_DESCRIPTION)
		{
			if (*printing_mod == W_LINE_BREAK)
				ft_printf("\n");
			ft_printf("%s:\n", parent->path);
			if (parent->status & PERMISSION_DENIED)
			{
				error_handler(PERMISSION_DENIED, parent->name);
				return ;
			}
		}
		if (parent->content &&
			(flags & get_flag_code('g') || flags & get_flag_code('l')))
			ft_printf("total %li\n", parent->total_size);
	}
	*printing_mod = W_LINE_BREAK;
//	if (flags & get_flag_code('l') || flags & get_flag_code('g'))
		print_one_column(parent->content, flags);
//	else
//		print_by_columns(parent);
}

void		print_invalids(t_node *head)
{
	t_node	*curr;

	if (head)
	{
		curr = head;
		while (curr)
		{
			error_handler(NO_SUCH_FILE_OR_DIR, curr->name);
			curr = curr->next;
		}
	}
}
