/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anakagaw <anakagaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:31:14 by yxu               #+#    #+#             */
/*   Updated: 2025/01/01 17:22:48 by anakagaw         ###   ########.fr       */
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
# include <stdbool.h>

# define PI 3.141592653589793
# define PI_2 1.57079632679489661923	/* pi/2 */

// exit_code
# define MANUAL_QUIT 0
# define INIT_ERR 1
# define RUN_ERR 2

// game config
# define MAX_MAP_ROWS 100
# define MAX_MAP_COLS 100
# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080
# define FOV PI_2
# define FINENESS 1920
# define PLAYER_SIZE 0.2
# define MOVE_SPEED 0.05 // must smaller than PLAYER_SIZE
# define CAMERA_TURN_SPEED 0.05

// element id
# define EID_WALL_N 'N'
# define EID_WALL_S 'S'
# define EID_WALL_W 'W'
# define EID_WALL_E 'E'

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
	unsigned char		id;
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

typedef struct s_point
{
	double	x;
	double	y;
}	t_point;

typedef struct s_player
{
	t_point	location;
	double	direction;
}	t_player;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_map		map;
	t_player	player;
}	t_game;

typedef struct s_ray
{
	t_point	origin;
	t_point	tail;
	double	direction;
	double	distance;
	char	intersection_direction;
}	t_ray;

typedef struct s_column
{
	t_ray	*ray;
	t_point	midpoint;
	double	height;
	t_image	*texture;
}	t_column;

// init
void	argv_checker(int argc, char **argv);
char	**read_map(char *path, t_game *game);
void	check_map(t_game *game);
int		is_element(char *line);
void	init_game(char *map_path, t_game *game);
void	init_player(t_game *game);

// game
int		key_handler(int key, t_game *game);
int		screenctl(t_game *game);

// exit
int		close_win_handler(t_game *game);
void	clean_exit(int exitcode, char *errmsg, t_game *game);

// map utils
void	free_map(t_game *game);
// void	print_layout(char **layout);
t_image	*get_texture_with_id(t_game *game, unsigned char id);
int		load_texture(t_game *game, char *filepath, unsigned char id);
void	change_space_to_zero(t_map *map);

// image utils
int		create_trgb(int t, int r, int g, int b);
void	ft_mlx_pixel_put(t_image *image, int x, int y, int color);
int		ft_mlx_get_image_pixel(t_image *image, double x_ratio, double y_ratio);

// ray casting utils
void	to_next_intersection(t_ray *ray);
t_ray	*ray_casting(t_map map, t_player player);

// utils
int		count_line(char *path);
int		is_number(const char *str);
void	free2(char **p);
double	limit_angle(double angle);
double	min(double x1, double x2);
char	**rgb_split(char const *s, char c);

#endif
