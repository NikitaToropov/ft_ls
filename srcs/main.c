/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmissy <cmissy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 16:40:12 by cmissy            #+#    #+#             */
/*   Updated: 2021/01/10 13:09:26 by cmissy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int					main(int argc, char **argv)
{
	unsigned short	flags;

	(void)argc;
	flags = flags_parser_facade(&argv);
	dir_parser_facade(argv, flags);
	return (0);
}
