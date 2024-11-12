/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42tokyo.jp>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:31:14 by yxu               #+#    #+#             */
/*   Updated: 2024/11/12 22:43:21 by yxu              ###   ########.fr       */
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

// exit_codeの値
# define MANUAL_QUIT 0
# define ERR 1

// game設定
# define MAX_MAP_ROWS 100
# define MAX_MAP_COLS 100
# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080

typedef struct s_image
{
	void	*content;
	int		width;
	int		height;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_image;

typedef struct s_element
{
	int		x;
	int		y;
	char	orientation;
	t_image	texture;
}	t_element;

typedef struct s_map
{
	char		**content;
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

typedef struct s_textures
{
	t_image	wall_n;
	t_image	wall_s;
	t_image	wall_w;
	t_image	wall_e;
	t_image	floor;
	t_image	ceiling;
}	t_textures;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_map		map;
	t_player	player;
	t_textures	textures;
}	t_game;

// init
void	argv_checker(int argc, char **argv);
char	**read_map(char *path, t_game *game);
char	check_map_obj(char **map);
void	check_map(t_game *game);
void	init_game(char *map_path, t_game *game);

// game
int		key_handler(int key, t_game *game);
int		screenctl(t_game *game);

// exit
int		free_map(char **map);
void	free_game(t_game *game);
int		destory_win(t_game *game);
void	clean_exit(int exitcode, char *errmsg, t_game *game);

// tools
int		count_line(char *path);

#endif
