#include "ft_ls.h"

unsigned short get_flag_code(char flag)
{
	unsigned short result;
	size_t i;

	result = 0;
	i = 0;
	while(FLAGS[i])
	{
		if (flag == FLAGS[i])
			result |= 1 << i;
		i++;
	}
	return (result);
}

unsigned short parse_block(char *flags)
{
	unsigned short result;
	unsigned short flag_code;

	result = 0;
	while(*flags)
	{
		if (!(flag_code = get_flag_code(*flags)))
			error_handler(ILLEGAL_OPTON, flags);
		result |= flag_code;
		flags++;
	}
	return (result);
}

unsigned short flags_parser(char ***argv)
{
	unsigned result;

	result = 0;
	(*argv)++;
	while(**argv && **argv[0] && **argv[0] == '-' && **argv[0])
	{
		result |= parse_block(**argv + 1);
		(*argv)++;
	}
	return (result);
}
