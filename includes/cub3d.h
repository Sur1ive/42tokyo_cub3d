/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42tokyo.jp>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:31:14 by yxu               #+#    #+#             */
/*   Updated: 2024/11/12 00:29:51 by yxu              ###   ########.fr       */
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

# define MAX_MAP_ROWS 100
# define MAX_MAP_COLS 100
# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080

typedef struct s_image {
	void	*image;
	int		width;
	int		height;
}	t_image;

typedef struct s_mlx {
	void	*image;
	int		width;
	int		height;
}	t_mlx;

typedef struct s_data {
	void		*win;
	void		*mlx;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	char		**map;
	int			rows;
	int			cols;
	int			move_nb;
}	t_data;

void	clean_exit(int exitcode, char *errmsg, t_data *data);
void	check_map(t_data *data);
char	check_map_obj(char **map);
int		key_handler(int key, t_data *data);
void	init_game(char *map_path, t_data *data);
void	free_game(t_data *data);
int		count_line(char *path);
char	**read_map(char *path, t_data *data);
int		free_map(char **map);

#endif
