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

# define MEMCHECK(x) if (!x) exit(2)

# define ILLEGAL_OPTON			1
# define NO_SUCH_FILE_OR_DIR	2
# define PERMISSION_DENIED		3

# define WRONG_NAME				-1

# define SUCCESS				1
# define FAILURE				0
# define TRUE					1
# define FALSE					0

# define MORE					1
# define LESS					-1

# define FLAGS					"lRart"

typedef struct		s_date
{
	char			year;
	char			month;
	char			day;
	char			hour;
	char			minute;
	unsigned int	unix_time;
}					t_date;

typedef struct		s_format
{
	char			file_mod[10];
	unsigned short	num_of_links;
	char			*owner_name;
	char			*fie_group;
	float			file_size;
	struct s_date	date;
}					t_format;

typedef struct		s_dir
{
	long int	content_size;
	char			*name;
	char			*path;
	char			status;
	struct s_dir	*content;
	struct s_dir	*parent;
	struct s_dir	*next;
	struct s_format	description;
	struct stat		stat;
}					t_dir;

unsigned short		flags_parser(char ***argv);
unsigned short		get_flag_code(char flag);
t_dir				*dirs_parser(char **argv, unsigned short flags);
void				error_handler(char error_code, char *arg);
char				*ft_pathjoin(char *first, char *second);
char				compare_by_date(const t_dir *first, const t_dir *second);
char				compare_by_date_reverse(const t_dir *first,
						const t_dir *second);
char				compare_lexicographic(const t_dir *first,
						const t_dir *second);
char				compare_lexicographic_reverse(const t_dir *first,
						const t_dir *second);
void				push_front(t_dir **head, char *name, t_dir *parent);
void				sort_list_by(t_dir **head,
						char comparator(const t_dir *, const t_dir *));
void				del_t_dirs_recur(t_dir *head);
void				print_dirs_struct(t_dir *head, unsigned short flags);
//void				dir_handler(t_dir *node, unsigned short flags);
void				parse_format_recur(t_dir *head, unsigned short flags);
char				is_dummy_dir(t_dir *node);

#endif
