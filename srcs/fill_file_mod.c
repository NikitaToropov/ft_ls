/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_file_mod.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmissy <cmissy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 15:37:23 by cmissy            #+#    #+#             */
/*   Updated: 2021/01/08 17:51:42 by enikole          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_file_mod.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmissy <cmissy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 15:37:23 by cmissy            #+#    #+#             */
/*   Updated: 2021/01/08 15:40:19 by cmissy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static char		extended_attributes(char *path)
{
	acl_t		acl;
	acl_entry_t	dummy;

	if (listxattr(path, NULL, 0, XATTR_NOFOLLOW) > 0)
		return ('@');
	acl = acl_get_link_np(path, ACL_TYPE_EXTENDED);
	if (acl && acl_get_entry(acl, ACL_FIRST_ENTRY, &dummy) == -1)
	{
		acl_free(acl);
		acl = NULL;
	}
	if (acl)
	{
		acl_free(acl);
		return ('+');
	}
	return (' ');
}

void			fill_file_mod(t_node *node, struct stat stt)
{
	node->file_mod[0] = S_ISDIR(stt.st_mode) ? 'd' : '-';
	node->file_mod[0] = S_ISLNK(stt.st_mode) ? 'l' : node->file_mod[0];
	node->file_mod[1] = (stt.st_mode & S_IRUSR) ? 'r' : '-';
	node->file_mod[2] = (stt.st_mode & S_IWUSR) ? 'w' : '-';
	node->file_mod[3] = (stt.st_mode & S_IXUSR) ? 'x' : '-';
	node->file_mod[4] = (stt.st_mode & S_IRGRP) ? 'r' : '-';
	node->file_mod[5] = (stt.st_mode & S_IWGRP) ? 'w' : '-';
	node->file_mod[6] = (stt.st_mode & S_IXGRP) ? 'x' : '-';
	node->file_mod[7] = (stt.st_mode & S_IROTH) ? 'r' : '-';
	node->file_mod[8] = (stt.st_mode & S_IWOTH) ? 'w' : '-';
	node->file_mod[9] = (stt.st_mode & S_IXOTH) ? 'x' : '-';
	node->file_mod[9] = (stt.st_mode & S_ISVTX) ? 't' : node->file_mod[9];
	node->file_mod[10] = extended_attributes(node->path);
}
