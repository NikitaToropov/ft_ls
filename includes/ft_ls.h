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
# include <time.h>
# include <grp.h>
# include <sys/types.h>
# include <sys/xattr.h>
# include <sys/acl.h>

# include "libft.h"
# include "ft_printf.h"

# define MEM_CHECK(x) if (!x) exit(2)


# define ILLEGAL_OPTION			1

/**
 * Nodes statuses.
 */
# define NO_SUCH_FILE_OR_DIR	2
# define PERMISSION_DENIED		4
# define DIRECTORY				8
# define DUMMY_DIR				16
# define FILE					32

# define SUCCESS				1
# define FAILURE				0
# define TRUE					1
# define FALSE					0

# define MORE					1
# define LESS					-1
# define SIX_MONTHS				15770000

# define FLAGS					"lRartuUfg"
# define SYM_LINK_ARROW			" -> "
# define USER_N_T				"/Users/nikita_toropov"
# define DEFAULT_BUFF_SIZE		16

# define ROOT					"root"
# define ADMIN					"admin"



typedef struct		s_helper
{
	long int 		sum_block;
	off_t			biggest_file_size;
	size_t			longest_owner;
	size_t			longest_group;
	long int		sum_blocks;
}					t_helper;

typedef struct		s_format
{
	size_t			owner_len;
	size_t			size_len;
	size_t			group_len;
}					t_format;

typedef struct		s_dir
{
	char			status;

	char			*name;
	char			*path;
	long int		total_size;

	time_t			node_sec_time;
	time_t			node_nsec_time;
	char			date[13];

	char			*sym_link;
	nlink_t			num_of_links;
	off_t			size_in_bytes;
	char			*owner_name;
	char			*group_name;
	char			file_mod[20];

	struct group	*group;
	struct stat		stat;
	struct passwd	*passwd;

	struct s_format	format;

	struct s_dir	*content;
	struct s_dir	*parent;
	struct s_dir	*next;
}					t_dir;

/**
 * Utils.
 */
unsigned short		get_flag_code(char flag);
void				error_handler(char error_code, char *arg);
char				*ft_pathjoin(char *first, char *second);
char				is_dummy_dir(t_dir *node);

/**
 * "t_dirs" utils.
 */
void				push_back(t_dir **head, char *name, t_dir *parent);
void				del_t_dirs_recur(t_dir *head);
void				fill_time(t_dir *node, unsigned short flags);
void				fill_group_name(t_dir *node, unsigned short flags);
void				fill_owner_name(t_dir *node, unsigned short flags);
void				fill_sym_link(t_dir *node, unsigned short flags);
void				fill_file_mod(t_dir *node, unsigned short flags);
void 				fill_total(t_dir *node, long int total);
void				fill_format(t_dir *node, unsigned short flags,
						t_helper helper);


/**
 * t_dir comparators.
 */
char				compare_by_date(const t_dir *first, const t_dir *second);
char				compare_by_date_reverse(const t_dir *first,
											const t_dir *second);
char				compare_lexicographic(const t_dir *first,
										  const t_dir *second);
char				compare_lexicographic_reverse(const t_dir *first,
												  const t_dir *second);

/**
 * Parsers.
 */
unsigned short		flags_parser_facade(char ***argv);
t_dir				*dir_parser_facade(char **argv, unsigned short flags);
void				parse_nodes_recursively(t_dir **content_head,
											t_dir *parent, unsigned short flags);

/**
 * Sorting.
 */
void				t_dirs_sorting_by_flags_facade(t_dir **head,
						unsigned short flags);
t_dir				*get_tail(t_dir *node);
t_dir				*quick_sort_t_dirs_recur(t_dir *head, t_dir *end,
						char comparator(const t_dir *, const t_dir *));

/**
 * Printing.
 */
void				print_dirs_struct(t_dir *head, unsigned short flags);

#endif
