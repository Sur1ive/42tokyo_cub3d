/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenctl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42tokyo.jp>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 22:41:58 by yxu               #+#    #+#             */
/*   Updated: 2024/12/04 16:11:05 by yxu              ###   ########.fr       */
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

void	compute_next_intersection(double *x, double *y, double direction)
{
	const double	k = tan(direction);
	double	dx = floor(*x + 1) - *x;
	double	dy = floor(*y + 1) - *y;
	double	origin_x = *x;
	double	origin_y = *y;

	direction = limit_angle(direction);
	if (direction > PI / 2 && direction < PI * 3 / 2)
	{
		if (-k * dx - dy > 0)
		{
			*y = floor(*y + 1);
			*x = origin_x + (*y - origin_y) / k;
		}
		else if (-k * dx - dy < -1)
		{
			*y = ceil(*y - 1);
			*x = origin_x + (*y - origin_y) / k;
		}
		else
		{
			*x = ceil(*x - 1);
			*y = origin_y + (*x - origin_x) * k;
		}
	}
	else
	{
		if (k * dx - dy > 0)
		{
			*y = floor(*y + 1);
			*x = origin_x + (*y - origin_y) / k;
		}
		else if (k * dx - dy < -1)
		{
			*y = ceil(*y - 1);
			*x = origin_x + (*y - origin_y) / k;
		}
		else
		{
			*x = floor(*x + 1);
			*y = origin_y + (*x - origin_x) * k;
		}
	}
}

double	calculate_ray_distance(t_map map, double origin_x, double origin_y, double direction)
{
	double	x;
	double	y;
	int		x1;
	int		y1;

	direction = limit_angle(direction);
	x = origin_x;
	y = origin_y;
	while (1)
	{
		compute_next_intersection(&x, &y, direction);
		// printf("x: %.2f, y: %.2f\n", x, y);
		if (floor(x) == x)
		{
			y1 = floor(y);
			if (x > origin_x)
				x1 = x;
			else
				x1 = x - 1;
		}
		else
		{
			x1 = floor(x);
			if (y > origin_y)
				y1 = y;
			else
				y1 = y - 1;
		}
		// printf("x1: %d, y1: %d\n", x1, y1);
		if (x1 < 0 || x1 >= map.cols || y1 < 0 || y1 >= map.rows)
			return (INFINITY);
		if (map.layout[y1][x1] == '1')
			return (sqrt(pow(x - origin_x, 2) + pow(y - origin_y, 2)));
	}
}

double	*ray_casting(t_map map, t_player player)
{
	double	*ray_distance_array;
	int		i;
	double	direction;

	ray_distance_array = (double *)malloc(sizeof(double) * GAME_FINENESS);
	i = 0;
	while (i < GAME_FINENESS)
	{
		direction = player.direction - GAME_FOV / 2 + GAME_FOV / GAME_FINENESS * i ;
		ray_distance_array[i] = calculate_ray_distance(map, player.x, player.y, direction);
		// printf("direction: %.2f distance: %.2f\n", direction, ray_distance_array[i]);
		i++;
	}
	return (ray_distance_array);
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
			height = 1.0 / (2 * ray_distance_array[i] * tan(GAME_FOV / 2)) * WIN_WIDTH / cos(i * GAME_FOV / GAME_FINENESS - GAME_FOV / 2);
		if (height >= WIN_HEIGHT)
			height = WIN_HEIGHT;
		midpoint.x = (0.5 + tan(i * GAME_FOV / GAME_FINENESS - GAME_FOV / 2) / (2 * tan(GAME_FOV / 2))) * WIN_WIDTH;
		midpoint.y = WIN_HEIGHT / 2;
		p1.x = midpoint.x;
		p1.y = midpoint.y - height / 2;
		p2.x = midpoint.x;
		p2.y = midpoint.y + height / 2;
		// printf("p1x: %d, p1y: %d, p2x: %d, p2y: %d\n", (int)p1.x, (int)p1.y, (int)p2.x, (int)p2.y);
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
