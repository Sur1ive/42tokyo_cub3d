/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenctl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42tokyo.jp>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 22:41:58 by yxu               #+#    #+#             */
/*   Updated: 2024/12/10 22:41:38 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_background(t_image *frame, int floor_color, int ceiling_color)
{
	int	x;
	int	y;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			if (y < WIN_HEIGHT / 2)
				ft_mlx_pixel_put(frame, x, y, ceiling_color);
			else
				ft_mlx_pixel_put(frame, x, y, floor_color);
			x++;
		}
		y++;
	}
}

static t_column	create_column(int i, t_ray *ray, t_game *game)
{
	t_column	column;
	double		fish_eye_offset;
	double		angle;

	angle = atan((i - FINENESS / 2) * 2 * tan(FOV / 2) / FINENESS);
	fish_eye_offset = 1 / cos(angle);
	column.height = 1.0 / (2 * ray->distance * tan(FOV / 2)) * WIN_WIDTH
		* fish_eye_offset;
	column.midpoint.x = i;
	column.midpoint.y = WIN_HEIGHT / 2;
	column.texture = get_texture_with_id(game, ray->intersection_direction);
	column.ray = ray;
	return (column);
}

static void	draw_column(t_image *frame, t_column *column)
{
	int				y;
	double			x_ratio;
	double			y_ratio;
	const double	height = column->height;
	const t_point	p = column->ray->tail;

	y = column->midpoint.y - height / 2;
	if (y < 0)
		y = 0;
	if (p.x == floor(p.x))
		x_ratio = p.y - floor(p.y);
	else
		x_ratio = p.x - floor(p.x);
	while (y <= min(WIN_HEIGHT, column->midpoint.y + height / 2))
	{
		y_ratio = (y - (column->midpoint.y - height / 2)) / height;
		ft_mlx_pixel_put(frame, column->midpoint.x, y,
			ft_mlx_get_image_pixel(column->texture, x_ratio, y_ratio));
		y++;
	}
}

static void	draw_wall(t_image *frame, t_game *game, t_ray *ray_array)
{
	int			i;
	t_column	column;

	i = 0;
	while (i < FINENESS)
	{
		column = create_column(i, &ray_array[i], game);
		draw_column(frame, &column);
		i++;
	}
}

int	screenctl(t_game *game)
{
	t_image	frame;
	t_ray	*ray_array;

	frame.img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	frame.addr = mlx_get_data_addr(frame.img, &frame.bits_per_pixel,
			&frame.line_length, &frame.endian);
	draw_background(&frame, game->map.floor_color, game->map.ceiling_color);
	ray_array = ray_casting(game->map, game->player);
	if (ray_array == NULL)
		clean_exit(RUN_ERR, "malloc error", game);
	draw_wall(&frame, game, ray_array);
	free(ray_array);
	mlx_put_image_to_window(game->mlx, game->win, frame.img, 0, 0);
	mlx_destroy_image(game->mlx, frame.img);
	return (0);
}
