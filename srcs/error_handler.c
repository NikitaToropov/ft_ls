#include "ft_ls.h"

void error_handler(char error_code, char *arg)
{
	if (error_code == ILLEGAL_OPTION)
	{
		write(STDERR_FILENO, "ls: illegal option -- ", 22);
		write(STDERR_FILENO, arg, 1);
		write(STDERR_FILENO, "\nusage: ls [-", 13);
		write(STDERR_FILENO, FLAGS, ft_strlen(FLAGS));
		write(STDERR_FILENO, "] [file ...]\n", 13);
		exit(1);
	}
	else if (error_code == NO_SUCH_FILE_OR_DIR)
	{
		write(STDERR_FILENO, "ls: ", 4);
		write(STDERR_FILENO, arg, ft_strlen(arg));
		write(STDERR_FILENO, ": No such file or directory\n", 28);
	}
	else if (error_code == PERMISSION_DENIED)
	{
		write(STDERR_FILENO, "ls: ", 4);
		write(STDERR_FILENO, arg, ft_strlen(arg));
		write(STDERR_FILENO, " Permission denied\n", 19);
	}
	else
		ft_printf("Dude something wrong in your code");
}
