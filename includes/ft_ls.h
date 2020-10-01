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

# define ILLEGAL_OPTON 1
# define NO_SUCH_FILE_OR_DIR 2
# define PERMISSION_DENIED 3

# define L_FLAG 'l'
# define R_UPP_FLAG 'R'
# define A_FLAG 'a'
# define R_FLAG 'r'
# define T_FLAG 't'

static char g_flags[] = {L_FLAG, R_UPP_FLAG, A_FLAG, R_FLAG, T_FLAG, '\0'};

unsigned short flags_parser(char **argv);
unsigned short get_flag_code(char flag);
void error_handler(char error_code, char *arg);


#endif
