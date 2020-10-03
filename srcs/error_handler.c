#include "ft_ls.h"

void error_handler(char error_code, char *arg)
{
	if (error_code == ILLEGAL_OPTON)
	{
		ft_printf("ls: illegal option -- %c\n"
			"\"usage: ls [-%s] [file ...]\"\n",
			*arg, FLAGS);
		exit(1);
	}
	else if (error_code == NO_SUCH_FILE_OR_DIR)
		ft_printf("ls: %s: No such file or directory\n", arg);
	else if (error_code == PERMISSION_DENIED)
		ft_printf("ls: %s: Permission denied\n", arg);
	else
		ft_printf("Dude something wrong in your code");
}
