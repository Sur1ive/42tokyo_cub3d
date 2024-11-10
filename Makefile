NAME	= cub3D
SRC_DIR = srcs/
SRCS	=
SRCS	:= $(addprefix $(SRC_DIR), $(SRCS))
OBJS	= $(SRCS:.c=.o)
LIB		= ./libft/libft.a
CC		= cc
CFLAGS	= -Wall -Wextra -Werror -Imlx -Iincludes

all: $(NAME)

$(NAME): $(OBJS)
	make -C libft
	$(CC) $(CFLAGS) $(OBJS) $(LIB) -Lmlx -lmlx -lXext -lX11 -o $(NAME)

clean:
	rm -rf $(OBJS)
	make clean -C libft

fclean: clean
	rm -rf $(NAME)
	make fclean -C libft

re: fclean all

.PHONY: all clean fclean re
