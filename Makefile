NAME = ft_ls

# dirs
DIR_S = srcs
DIR_O = objs
DIR_L = libft

INCLUDES = ./includes
INCLUDES_L = ./libft/includes
INCLUDES_P = ./libft/ft_printf/includes

# files
C_FILES = main.c \
			parse_flags.c \

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
	#gcc -g -I $(INCLUDES) -I $(INCLUDES_L) -I $(INCLUDES_P) -c $< -o $@

$(LIBFT): force
	make -C $(DIR_L)

clean:
	rm -rf $(DIR_O)
	make -C $(DIR_L) clean

fclean: clean
	rm -f $(NAME)
	make -C $(DIR_L) fclean

re: fclean all