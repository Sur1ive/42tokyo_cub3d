/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenctl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 22:41:58 by yxu               #+#    #+#             */
/*   Updated: 2024/12/07 19:00:10 by yxu              ###   ########.fr       */
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

void	drawline(t_image *frame, t_point p1, t_point p2, int color)
{
	int	fineness;
	int	i;

	fineness = sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2)) + 1;
	i = 0;
	while (i <= fineness)
	{
		ft_mlx_pixel_put(frame, round(p1.x + (p2.x - p1.x) / fineness * i),
			round(p1.y + (p2.y - p1.y) / fineness * i), color);
		i++;
	}
}

void	draw_wall(t_image *frame, t_game *game)
{
	double	*ray_distance_array;
	int		i;
	double	height;
	t_point midpoint;
	t_point p1;
	t_point p2;

	ray_distance_array = ray_casting(game->map, game->player);
	i = 0;
	while (i < GAME_FINENESS)
	{
		if (ray_distance_array[i] == 0)
			height = INFINITY;
		else
			height = 1.0 / (2 * ray_distance_array[i] * tan(GAME_FOV / 2)) * WIN_WIDTH / cos(atan((i - GAME_FINENESS / 2) * 2 * tan(GAME_FOV / 2) / GAME_FINENESS));
		if (height >= WIN_HEIGHT)
			height = WIN_HEIGHT;
		midpoint.x = i;
		midpoint.y = WIN_HEIGHT / 2;
		p1.x = midpoint.x;
		p1.y = midpoint.y - height / 2;
		p2.x = midpoint.x;
		p2.y = midpoint.y + height / 2;
		drawline(frame, p1, p2, create_trgb(0, 10 * ray_distance_array[i], 10 * ray_distance_array[i], 10 * ray_distance_array[i]));
		i++;
	}
	free(ray_distance_array);
}

int	screenctl(t_game *game)
{
	t_image	frame;

	frame.img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	frame.addr = mlx_get_data_addr(frame.img, &frame.bits_per_pixel,
			&frame.line_length, &frame.endian);
	draw_background(&frame, game->map.floor_color, game->map.ceiling_color);
	draw_wall(&frame, game);
	mlx_put_image_to_window(game->mlx, game->win, frame.img, 0, 0);
	mlx_destroy_image(game->mlx, frame.img);
	return (0);
}
