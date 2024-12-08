NAME	= cub3D
SRC_DIR = srcs/
SRCS	= main.c init.c exit.c argv_checker.c utils.c key_handler.c\
		map_checker.c map_utils.c map_parser.c\
		image_utils.c screenctl.c\
		ray_utils.c ray_casting.c
SRCS	:= $(addprefix $(SRC_DIR), $(SRCS))
OBJS	= $(SRCS:.c=.o)
LIB		= ./libft/libft.a
CC		= cc
CFLAGS	= -Wall -Wextra -Werror -Imlx -Iincludes

all: $(NAME)

$(NAME): $(OBJS)
	make -C libft
	$(CC) $(CFLAGS) $(OBJS) $(LIB) mlx/libmlx_Linux.a -lXext -lX11 -lm -fsanitize=address -o $(NAME)

clean:
	rm -rf $(OBJS)
	make clean -C libft

fclean: clean
	rm -rf $(NAME)
	make fclean -C libft

re: fclean all

.PHONY: all clean fclean re
