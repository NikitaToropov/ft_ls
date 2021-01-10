/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dirs_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmissy <cmissy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 13:16:37 by cmissy            #+#    #+#             */
/*   Updated: 2021/01/10 14:10:04 by cmissy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_node		*stat_handler(t_node *node, unsigned short flags)
{
	struct passwd	*passwd;
	struct stat		stat;

	lstat(node->path, &(stat));
	fill_time(node, flags, stat);
	node->group_name = getgrgid(stat.st_gid)->gr_name;
	fill_sym_link(node, stat);
	fill_file_mod(node, stat);
	passwd = getpwuid(stat.st_uid);
	node->owner_name = (passwd) ? ft_strdup(passwd->pw_name)
								: ft_itoa(stat.st_uid);
	node->blocks = stat.st_blocks;
	node->num_of_links = stat.st_nlink;
	node->size_in_bytes = stat.st_size;
	node->status |= (S_ISDIR(stat.st_mode)) ? DIRECTORY : FILE;
	node->status = (node->status & DIRECTORY && is_dummy_dir(node))
					? DUMMY_DIR
					: node->status;
	if (node->parent)
	{
		node->parent->total_size += node->blocks;
		fill_format(node->parent, node);
	}
	return (node);
}

void				parse_the_dir(t_node *parent, unsigned short flags,
									char *printing_mod)
{
	DIR				*dir;
	struct dirent	*dirent;
	t_node			*curr;

	if (!parent)
		return ;
	if ((dir = opendir(parent->path)))
	{
		while ((dirent = readdir(dir)))
		{
			if (dirent->d_name[0] == '.'
				&& !(flags & get_flag_code('a') || flags & get_flag_code('f')))
				continue;
			curr = stat_handler(new_t_dir(dirent->d_name, parent), flags);
			curr->next = parent->content;
			parent->content = curr;
		}
		closedir(dir);
		nodes_sorting_by_flags(&(parent->content), flags);
		print_dir(parent, flags, printing_mod);
	}
	else
		error_handler(PERMISSION_DENIED, parent->name);
}

static void			init_dirs_files_invalids(t_facade *facade, char **argv,
											unsigned short flags)
{
	struct stat		stt;

	ft_bzero(facade, sizeof(t_facade));
	if (*argv == NULL)
		facade->dirs = stat_handler(new_t_dir(".", NULL), flags);
	while (*argv != NULL)
	{
		if (lstat(*argv, &stt) != -1)
		{
			if (S_ISDIR(stt.st_mode))
				insert_order_by(&(facade->dirs),
					stat_handler(new_t_dir(*argv, NULL), flags), flags);
			else
				insert_order_by(&(facade->files_parent.content),
					stat_handler(new_t_dir(*argv, &(facade->files_parent)),
						flags), flags);
		}
		else
			insert_order_by(&(facade->invalid_nodes), new_t_dir(*argv, NULL),
				0);
		argv++;
	}
}

void				dir_parser_facade(char **argv, unsigned short flags)
{
	t_facade		facade;
	char			printing_mod;

	init_dirs_files_invalids(&facade, argv, flags);
	if (facade.files_parent.content)
		printing_mod = W_LINE_BREAK;
	else if (!facade.files_parent.content
			&& facade.dirs
			&& !(facade.dirs->next))
		printing_mod = WO_DIR_DESCRIPTION;
	else
		printing_mod = WO_LINE_BREAK;
	print_invalids(facade.invalid_nodes);
	print_dir(&(facade.files_parent), flags, &printing_mod);
	if (flags & get_flag_code('R'))
		recursive_dir_printing(facade.dirs, flags, &printing_mod);
	else
		simple_dir_printing(facade.dirs, flags, &printing_mod);
	del_line_of_nodes(&(facade.invalid_nodes));
	del_line_of_nodes(&(facade.dirs));
	del_line_of_nodes(&((facade.files_parent).content));
}
