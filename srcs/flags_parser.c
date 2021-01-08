/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmissy <cmissy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 16:34:41 by cmissy            #+#    #+#             */
/*   Updated: 2021/01/08 17:51:42 by enikole          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmissy <cmissy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 16:34:41 by cmissy            #+#    #+#             */
/*   Updated: 2021/01/08 16:37:21 by cmissy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

unsigned short		get_flag_code(char flag)
{
	unsigned short	result;
	size_t			i;

	result = 0;
	i = 0;
	while (FLAGS[i])
	{
		if (flag == FLAGS[i])
			result |= 1 << i;
		i++;
	}
	return (result);
}

static void			flags_handler(char flag, unsigned short *flags)
{
	if (flag == 'U')
		*flags &= ~(get_flag_code('u'));
	else if (flag == 'u')
		*flags &= ~(get_flag_code('U'));
}

unsigned short		parse_the_flags_string(char *flags)
{
	unsigned short	result;
	unsigned short	flag_code;

	result = 0;
	while (*flags)
	{
		if (!(flag_code = get_flag_code(*flags)))
			error_handler(ILLEGAL_OPTION, flags);
		result |= flag_code;
		flags_handler(*flags, &result);
		flags++;
	}
	return (result);
}

unsigned short		flags_parser_facade(char ***argv)
{
	unsigned short	result;

	result = 0;
	(*argv)++;
	while (**argv && **argv[0] && **argv[0] == '-' && **argv[0])
	{
		result |= parse_the_flags_string(**argv + 1);
		(*argv)++;
	}
	return (result);
}
