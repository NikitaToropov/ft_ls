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

# include <dirent.h>
# include <sys/stat.h>

# include "libft.h"
# include "ft_printf.h"

typedef struct		s_format
{
	char			**files_or_dirs;
	size_t			num_of_files_or_dirs;
	size_t			flags;
	char			**argv;
	int				argc;
}					t_format;

void				init_format_struct(int argc, char **argv, t_format *format);

#endif
