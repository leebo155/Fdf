CC = cc
CFLAGS = -Wall -Wextra -Werror
INC = -Iinclude
NAME = fdf
SRCS = src/ft_make_map.c \
	   src/ft_make_new_mlx_window.c \
	   src/ft_atoss.c \
	   src/ft_new_instruction.c \
	   src/ft_check_input_file.c \
	   src/ft_coordinates.c	\
	   src/ft_draw_line.c \
	   src/ft_draw_pixel.c \
	   src/main.c \
	   src/ft_hook_utils.c
OBJS = $(SRCS:.c=.o)
LIBFT = lib/libft.a
FT_PRINTF = lib/libftprintf.a
GNL = lib/libgnl.a
MLXLIB = lib/libmlx.a
EXTRA_CFLAGS = -framework OpenGL -framework Appkit

.PHONY: all clean fclean re

all: $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean
	$(MAKE) all

$(NAME): $(LIBFT) $(FT_PRINTF) $(GNL) $(MLXLIB) $(OBJS)
	$(CC) $(CFLAGS) $(EXTRA_CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) $(INC) -c -o $@ $^
