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

/**
 * Flags error status.
 */
# define ILLEGAL_OPTION			1

/**
 * Nodes statuses.
 */
# define NO_SUCH_FILE_OR_DIR	2
# define PERMISSION_DENIED		4
# define DIRECTORY				8
# define DUMMY_DIR				16
# define FILE					32

/**
 * Utility definitions.
 */
# define SUCCESS				1
# define FAILURE				0
# define TRUE					1
# define FALSE					0
# define MORE					1
# define LESS					-1
# define SIX_MONTHS				15770000
# define SYM_LINK_ARROW			" -> "
# define DEFAULT_BUFF_SIZE		16

/**
 * Formatting strings.
 */
# define L_FORMATTING			"%s %*u %-*s  %-*s  %*lli %s %s%s\n"
# define G_FORMATTING			"%s %*u %6$-*s  %*lli %s %s%s\n"

/**
 * All flags.
 */
# define FLAGS					"lRartuUfg"


typedef struct		s_dir_format
{
	size_t			num_of_files;
	size_t			name_len;
	size_t			owner_len;
	size_t			size_len;
	size_t			group_len;
	size_t			num_of_links_len;
}					t_dir_format;

typedef struct		s_node
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

	blkcnt_t		blocks;

	struct group	*group;
	struct stat		stat;
	struct passwd	*passwd;

	struct s_dir_format	format;

	struct s_node	*content;
	struct s_node	*parent;
	struct s_node	*next;
}					t_node;

typedef struct		s_facade
{
	struct s_node	*dirs;
	struct s_node	files;
}					t_facade;

/**
 * Utils.
 */
unsigned short		get_flag_code(char flag);
void				error_handler(char error_code, char *arg);
char				*ft_pathjoin(char *first, char *second);
char				is_dummy_dir(t_node *node);

/**
 * "t_nodes" utils.
 */
void				push_back(t_node **head, char *name, t_node *parent);
void				del_nodes_recur(t_node *head);
void				fill_time(t_node *node, unsigned short flags);
void				fill_group_name(t_node *node, unsigned short flags);
void				fill_owner_name(t_node *node, unsigned short flags);
void				fill_sym_link(t_node *node, unsigned short flags);
void				fill_file_mod(t_node *node, unsigned short flags);
void				fill_format(t_node *parent, unsigned short
						flags, t_node *curr);

/**
 * t_node comparators.
 */
char				compare_by_date(const t_node *first, const t_node *second);
char				compare_by_date_reverse(const t_node *first,
						const t_node *second);
char				compare_lexicographic(const t_node *first,
						const t_node *second);
char				compare_lexicographic_reverse(const t_node *first,
						const t_node *second);

/**
 * Parsers.
 */
unsigned short		flags_parser_facade(char ***argv);
void				dir_parser_facade(t_facade *facade, char **argv,
						unsigned short flags);
void				parse_nodes_recursively(t_node **content_head,
						t_node *parent, unsigned short flags);

/**
 * Sorting.
 */
void				nodes_sorting_by_flags_facade(t_node **head,
						unsigned short flags);
t_node				*get_tail(t_node *node);
t_node				*quick_sort_nodes_recur(t_node *head, t_node *end,
						char comparator(const t_node *, const t_node *));

/**
 * Printing.
 */
void				print_dirs_struct(t_facade facade, unsigned short flags);

#endif
