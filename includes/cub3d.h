/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42tokyo.jp>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:31:14 by yxu               #+#    #+#             */
/*   Updated: 2024/12/03 01:58:52 by yxu              ###   ########.fr       */
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

#define PI 3.141592653589793

// exit_code
# define MANUAL_QUIT 0
# define INIT_ERR 1
# define RUN_ERR 2

// game config
# define MAX_MAP_ROWS 100
# define MAX_MAP_COLS 100
# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080
# define GAME_FOV 2 * PI / 3
# define GAME_FINENESS 1920
# define PLAYER_SIZE 0.2
# define MOVE_SPEED 0.1

// element id
# define EID_WALL_N (unsigned char[]){'N', 'O'}
# define EID_WALL_S (unsigned char[]){'S', 'O'}
# define EID_WALL_W (unsigned char[]){'W', 'E'}
# define EID_WALL_E (unsigned char[]){'E', 'A'}
// # define EID_FLOOR (unsigned char[]){'F', '\0'}
// # define EID_CEILING (unsigned char[]){'C', '\0'}

typedef struct s_image
{
	void	*img;
	char	*addr;
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
	int			floor_color;
	int			ceiling_color;
	t_element	*elements;
}	t_map;

typedef struct s_player
{
	double	x;
	double	y;
	double	direction;
}	t_player;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_map		map;
	t_player	player;
}	t_game;

typedef struct s_point {
double	x;
double	y;
double	z;
}	t_point;

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

// map utils
void	free_map(t_game *game);
void	print_layout(char **layout);
void	*get_texture_with_id(t_game *game, unsigned char id[2]);
void	load_texture(t_game *game, char *filepath, unsigned char id[2]);
void	mock_map_maker(t_game *game);

// image utils
int		create_trgb(int t, int r, int g, int b);
void	ft_mlx_pixel_put(t_image *image, int x, int y, int color);

// utils
int		count_line(char *path);
void	free2(char **p);
double	limit_angle(double angle);

#endif
