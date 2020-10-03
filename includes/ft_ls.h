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
# include <pwd.h>

# include "libft.h"
# include "ft_printf.h"

#define MEMCHECK(x) if (!x) exit(2)

# define ILLEGAL_OPTON			1
# define NO_SUCH_FILE_OR_DIR	2
# define PERMISSION_DENIED		3
# define TRUE					1
# define FALSE					0
# define FLAGS					"lRart"

typedef struct		s_format
{

}					t_format;
typedef struct		s_dir
{
	char			*name;
	struct s_dir	*content;
	struct s_dir	*next;
	struct s_format	format;
}					t_dir;

unsigned short	flags_parser(char ***argv);
unsigned short	get_flag_code(char flag);
t_dir			*dirs_parser(char **argv, unsigned short flags);

void			error_handler(char error_code, char *arg);


#endif
