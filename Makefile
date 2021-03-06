NAME = ft_ls

# dirs
DIR_S = srcs
DIR_O = objs
DIR_L = libft

INCLUDES = ./includes
INCLUDES_L = ./libft/includes
INCLUDES_P = ./libft/ft_printf/includes

# files
C_FILES = comparators.c \
		dirs_parser.c \
		error_handler.c \
		flags_parser.c \
		main.c \
		t_node_utils.c \
		utils.c \
		print_dir_structure.c \
		fill_time.c \
		fill_sym_link.c \
		fill_file_mod.c \
		fill_format.c \
		print_by_column.c \
		print_long_listing.c \
		quick_sort_t_dirs_recur.c \

HEADER = $(INCLUDES)/ft_ls.h
SRCS = $(addprefix $(DIR_S)/,$(C_FILES))
OBJS = $(addprefix $(DIR_O)/,$(C_FILES:.c=.o))\

#libft.a
LIBFT = $(DIR_L)/libft.a

.PHONY: all clean fclean re reclean force

all: $(NAME)

$(NAME): $(LIBFT) $(DIR_O) $(OBJS)
	gcc -Wall -Wextra -Werror $(OBJS) -L $(DIR_L) -lft -o $@

$(DIR_O):
	mkdir -p objs

$(DIR_O)/%.o: $(DIR_S)/%.c $(HEADER)
	gcc -Wall -Wextra -Werror -g -I $(INCLUDES) -I $(INCLUDES_L) -I $(INCLUDES_P) -c $< -o $@

$(LIBFT): force
	make -C $(DIR_L)

clean:
	rm -rf $(DIR_O)
	make -C $(DIR_L) clean

fclean: clean
	rm -f $(NAME)
	make -C $(DIR_L) fclean

re: fclean all
