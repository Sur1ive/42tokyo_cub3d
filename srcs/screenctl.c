/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenctl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42tokyo.jp>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 22:41:58 by yxu               #+#    #+#             */
/*   Updated: 2024/12/08 18:15:30 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_background(t_image *frame, int floor_color, int ceiling_color)
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

void	draw_column(t_image *frame, t_point midpoint, t_game *game, t_ray ray, double height)
{
	int		y;
	t_image	*texture;
	double	x_ratio;
	double	y_ratio;

	y = midpoint.y - height / 2;
	if (y < 0)
		y = 0;
	while (y <= min(WIN_HEIGHT, midpoint.y + height / 2))
	{
		if (ray.tail.x == floor(ray.tail.x))  // greedy
			x_ratio = ray.tail.y - floor(ray.tail.y);
		else
			x_ratio = ray.tail.x - floor(ray.tail.x);
		y_ratio = (y - (midpoint.y - height / 2)) / height;
		if (ray.intersection_direction == 'N')
			texture = get_texture_with_id(game, EID_WALL_N);
		if (ray.intersection_direction == 'S')
			texture = get_texture_with_id(game, EID_WALL_S);
		if (ray.intersection_direction == 'W')
			texture = get_texture_with_id(game, EID_WALL_W);
		if (ray.intersection_direction == 'E')
			texture = get_texture_with_id(game, EID_WALL_E);
		ft_mlx_pixel_put(frame, midpoint.x, y, ft_mlx_get_image_pixel(texture, x_ratio, y_ratio));
		y++;
	}
}

void	draw_wall(t_image *frame, t_game *game, t_ray *ray_array)
{
	int		i;
	double	height;
	double	fish_eye_offset;
	double	angle;
	t_point	midpoint;

	i = 0;
	while (i < FINENESS)
	{
		angle = atan((i - FINENESS / 2) * 2 * tan(FOV / 2) / FINENESS);
		fish_eye_offset = 1 / cos(angle);
		height = 1.0 / (2 * ray_array[i].distance * tan(FOV / 2)) * WIN_WIDTH
			* fish_eye_offset;
		midpoint.x = i;
		midpoint.y = WIN_HEIGHT / 2;
		draw_column(frame, midpoint, game, ray_array[i], height);
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
