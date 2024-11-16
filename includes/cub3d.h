/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42tokyo.jp>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:31:14 by yxu               #+#    #+#             */
/*   Updated: 2024/11/16 19:37:13 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include <stdio.h>
# include <string.h>
# include <math.h>
# include <fcntl.h>
# include <mlx.h>
# include <errno.h>
# include <sys/time.h>
# include <X11/X.h>
# include <X11/keysym.h>

// exit_code
# define MANUAL_QUIT 0
# define ERR 1

// game config
# define MAX_MAP_ROWS 100
# define MAX_MAP_COLS 100
# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080

// element id
# define EID_WALL_N "NO"
# define EID_WALL_S "SO"
# define EID_WALL_W "WE"
# define EID_WALL_E "EA"
# define EID_FLOOR "F"
# define EID_CEILING "C"

typedef struct s_image
{
	void	*img;
	int		width;
	int		height;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_image;

typedef struct s_element
{
	unsigned char		id[2];
	t_image				texture;
	struct s_element	*next;
}	t_element;

typedef struct s_map
{
	char		**layout;
	int			rows;
	int			cols;
	t_element	*elements;
}	t_map;

typedef struct s_player
{
	int		x;
	int		y;
	char	orientation;
}	t_player;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_map		map;
	t_player	player;
}	t_game;

// init
void	argv_checker(int argc, char **argv);
char	**read_map(char *path, t_game *game);
char	check_map_obj(char **layout);
void	check_map(t_game *game);
void	init_game(char *map_path, t_game *game);

// game
int		key_handler(int key, t_game *game);
int		screenctl(t_game *game);

// exit
int		close_win_handler(t_game *game);
void	clean_exit(int exitcode, char *errmsg, t_game *game);

// map tools
void	free_map(t_game *game);
void	print_layout(char **layout);
t_image	*get_texture_with_id(t_element *elements, unsigned char id[2]);

// tools
int		count_line(char *path);
void	free2(char **p);

#endif
