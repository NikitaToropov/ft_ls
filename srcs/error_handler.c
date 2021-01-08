/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enikole <enikole@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 17:49:05 by enikole           #+#    #+#             */
/*   Updated: 2021/01/08 18:01:30 by enikole          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	print_permission_denied(char *arg)
{
	write(STDERR_FILENO, "ls: ", 4);
	write(STDERR_FILENO, arg, ft_strlen(arg));
	write(STDERR_FILENO, ": No such file or directory\n", 28);
}

static void	print_no_such_file_or_dir(char *arg)
{
	write(STDERR_FILENO, "ls: ", 4);
	write(STDERR_FILENO, arg, ft_strlen(arg));
	write(STDERR_FILENO, ": No such file or directory\n", 28);
}

static void	print_illegal_option(char *arg)
{
	write(STDERR_FILENO, "ls: illegal option -- ", 22);
	write(STDERR_FILENO, arg, 1);
	write(STDERR_FILENO, "\nusage: ls [-", 13);
	write(STDERR_FILENO, FLAGS, ft_strlen(FLAGS));
	write(STDERR_FILENO, "] [file ...]\n", 13);
}

void		error_handler(char error_code, char *arg)
{
	if (error_code == ILLEGAL_OPTION)
	{
		print_illegal_option(arg);
		exit(1);
	}
	else if (error_code == NO_SUCH_FILE_OR_DIR)
		print_no_such_file_or_dir(arg);
	else if (error_code == PERMISSION_DENIED)
		print_permission_denied(arg);
	else
		ft_printf("Dude something wrong in your code");
}
