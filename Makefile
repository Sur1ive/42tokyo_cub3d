NAME	= cub3D
SRC_DIR = srcs/
SRCS	= main.c init.c init_player.c exit.c argv_checker.c utils.c key_handler.c\
		map_checker.c map_utils.c map_parser.c\
		image_utils.c screenctl.c rgb_split.c\
		ray_utils.c ray_casting.c
SRCS	:= $(addprefix $(SRC_DIR), $(SRCS))
OBJS	= $(SRCS:.c=.o)
LIB		= ./libft/libft.a mlx/libmlx_Linux.a
CC		= cc
CFLAGS	= -Wall -Wextra -Werror -Imlx -Iincludes

all: $(NAME)

$(LIB):
	make -C libft
	make -C mlx

$(NAME): $(LIB) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIB) -lXext -lX11 -lm -o $(NAME)

clean:
	rm -rf $(OBJS)
	make clean -C libft

fclean: clean
	rm -rf $(NAME)
	make fclean -C libft
	make clean -C mlx

re: fclean all

.PHONY: all clean fclean re
