#include "ft_ls.h"

static char extended_attributes(char *path)
{
	acl_t acl;
	acl_entry_t dummy;

	if (listxattr(path, NULL, 0, XATTR_NOFOLLOW) > 0)
		return '@';
	acl = acl_get_link_np(path, ACL_TYPE_EXTENDED);
	if (acl && acl_get_entry(acl, ACL_FIRST_ENTRY, &dummy) == -1)
	{
		acl_free(acl);
		acl = NULL;
	}
	if (acl)
	{
		acl_free(acl);
		return '+';
	}
	return ' ';
}

void fill_file_mod(t_node *node, unsigned short flags)
{
	(void) flags;
	node->file_mod[0] = S_ISDIR(node->stat.st_mode) ? 'd' : '-';
	node->file_mod[0] = S_ISLNK(node->stat.st_mode) ? 'l'
													: node->file_mod[0];
	node->file_mod[1] = (node->stat.st_mode & S_IRUSR) ? 'r' : '-';
	node->file_mod[2] = (node->stat.st_mode & S_IWUSR) ? 'w' : '-';
	node->file_mod[3] = (node->stat.st_mode & S_IXUSR) ? 'x' : '-';
	node->file_mod[4] = (node->stat.st_mode & S_IRGRP) ? 'r' : '-';
	node->file_mod[5] = (node->stat.st_mode & S_IWGRP) ? 'w' : '-';
	node->file_mod[6] = (node->stat.st_mode & S_IXGRP) ? 'x' : '-';
	node->file_mod[7] = (node->stat.st_mode & S_IROTH) ? 'r' : '-';
	node->file_mod[8] = (node->stat.st_mode & S_IWOTH) ? 'w' : '-';
	node->file_mod[9] = (node->stat.st_mode & S_IXOTH) ? 'x' : '-';
	node->file_mod[10] = extended_attributes(node->path);
}
