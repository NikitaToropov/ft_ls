/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmissy <cmissy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 14:13:50 by cmissy            #+#    #+#             */
/*   Updated: 2020/09/20 16:42:18 by cmissy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "libft.h"
# include "ft_printf.h"

typedef struct		s_format
{
	unsigned int	set_of_flags;
	char 			**argv;
	int 			argc;
}					t_format;

int					parse_flags(int argc, char **argv);
//void				run_program(int *format);

#endif
