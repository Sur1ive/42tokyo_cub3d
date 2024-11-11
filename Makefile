NAME	= cub3D
SRC_DIR = srcs/
SRCS	= main.c key_handler.c map_checker.c utils.c init.c map.c
SRCS	:= $(addprefix $(SRC_DIR), $(SRCS))
OBJS	= $(SRCS:.c=.o)
LIB		= ./libft/libft.a
CC		= cc
CFLAGS	= -Wall -Wextra -Werror -Imlx -Iincludes

all: $(NAME)

$(NAME): $(OBJS)
	make -C libft
	$(CC) $(CFLAGS) $(OBJS) $(LIB) mlx/libmlx_Linux.a -lXext -lX11 -o $(NAME)

clean:
	rm -rf $(OBJS)
	make clean -C libft

fclean: clean
	rm -rf $(NAME)
	make fclean -C libft

re: fclean all

.PHONY: all clean fclean re
