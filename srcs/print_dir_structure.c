#include "ft_ls.h"

void print_date(t_dir *dir, unsigned short flags)
{
	char month_day_time[13];
	char *full_date;

	// need check date more or less year
	(void) flags;
	full_date = ctime((const time_t*)&(dir->stat.st_mtimespec));
	ft_strncpy(month_day_time, full_date + 4, 12);
	month_day_time[12] = '\0';
	ft_printf("%s", month_day_time);
}


void print_dir_description(t_dir *dir, unsigned short flags)
{
	(void) flags;
	ft_printf("\n%s:\n%li\n", dir->path, dir->stat.st_blocks);
}

void print_content(t_dir *dir, unsigned short flags)
{
	(void) flags;
	ft_printf("% 7u ", dir->stat.st_size); // 7 need to change later
	print_date(dir, flags);
	ft_printf(" %s\n", dir->name);
}

void print_dirs_struct_recur(t_dir *head, unsigned short flags)
{
	t_dir *curr;

	(void) flags;
	curr = head;
	while(curr)
	{
		print_content(curr, flags);
		curr = curr->next;
	}
	curr = head;
	while(curr)
	{
		if (S_ISDIR(curr->stat.st_mode)
			&& is_dummy_dir(curr) == FALSE)
		{
			print_dir_description(curr, flags);
//			ft_printf("\n%s:\ntotal %u\n", curr->path, curr->stat.st_size);
			print_dirs_struct_recur(curr->content, flags);
		}
		curr = curr->next;
	}
}

void print_dirs_struct(t_dir *head, unsigned short flags)
{
	t_dir *node;

	node = head;
	if (node->next == NULL)
	{
		if (S_ISDIR(node->stat.st_mode))
			ft_printf("total %i\n", node->content_size);
		else if (node->status == 0)
		{
			print_content(node, flags);
			ft_printf("\n");
		}
		print_dirs_struct_recur(node->content, flags);
	}
	else
	{
		while(node)
		{
			if (S_ISDIR(node->stat.st_mode))
			{
				print_dir_description(node, flags);
				print_dirs_struct_recur(node->content, flags);
			}
			else if (node->status == 0)
			{
				print_content(node, flags);
				ft_printf("\n");
			}
			node = node->next;
		}
	}
}
