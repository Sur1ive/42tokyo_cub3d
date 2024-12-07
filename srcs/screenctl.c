/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenctl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 22:41:58 by yxu               #+#    #+#             */
/*   Updated: 2024/12/07 18:26:02 by yxu              ###   ########.fr       */
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

void	offset_from_gridline(double *x, double *y, double direction)
{
	const double	epsilon = 1e-6;

	if (*x == floor(*x))
	{
		if (direction > PI / 2 && direction < PI * 3 / 2)
			*x -= epsilon;
		else
			*x += epsilon;
	}
	if (*y == floor(*y))
	{
		if (direction > PI)
			*y -= epsilon;
		else
			*y += epsilon;
	}
}

char	intersection_direction(double *x, double *y, double k, double direction)
{
	double	dx;
	double	dy;

	dx = floor(*x + 1) - *x;
	dy = floor(*y + 1) - *y;

if (direction > PI / 2 && direction < PI * 3 / 2)
	dx = 1 - dx;
// if (direction > PI)
// 	dy = 1 - dy;

	if (direction > PI / 2 && direction < PI * 3 / 2)
	{
		if (-k * dx - dy > 0)
			return ('S');
		else if (-k * dx - dy < -1)
			return ('N');
		else
			return ('W');
	}
	else
	{
		if (k * dx - dy > 0)
			return ('S');
		else if (k * dx - dy < -1)
			return ('N');
		else
			return ('E');
	}
}

void	compute_next_intersection(double *x, double *y, double k,
	char next_intersection_direction)
{
	const double	origin_x = *x;
	const double	origin_y = *y;

	if (next_intersection_direction == 'N')
	{
		*y = ceil(*y - 1);
		*x = origin_x + (*y - origin_y) / k;
	}
	if (next_intersection_direction == 'S')
	{
		*y = floor(*y + 1);
		*x = origin_x + (*y - origin_y) / k;
	}
	if (next_intersection_direction == 'W')
	{
		*x = ceil(*x - 1);
		*y = origin_y + (*x - origin_x) * k;
	}
	if (next_intersection_direction == 'E')
	{
		*x = floor(*x + 1);
		*y = origin_y + (*x - origin_x) * k;
	}
}

void	to_next_intersection(double *x, double *y, double direction)
{
	const double	k = tan(direction);
	const double	origin_x = *x;
	const double	origin_y = *y;
	char			next_intersection_direction;

	direction = limit_angle(direction);
	offset_from_gridline(x, y, direction);
	next_intersection_direction = intersection_direction(x, y, k, direction);
	compute_next_intersection(x, y, k, next_intersection_direction);
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
		to_next_intersection(&x, &y, direction);
		// if (floor(x) == x && floor(y) == y)
		// {
		// 	x1 = x;
		// 	y1 = y;
		// 	if (x1 < 0 || y1 < 0 || map.layout[y1][x1] == '\0')
		// 		return (INFINITY);
		// 	if (map.layout[y1 - 1][x1] == '1' || map.layout[y1][x1 - 1] == '1'
		// 	|| map.layout[y1][x1] == '1' || map.layout[y1 - 1][x1 - 1] == '1')
		// 		return (sqrt(pow(x - origin_x, 2) + pow(y - origin_y, 2)));
		// 	else
		// 		return
		// }
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
		if (x1 < 0 || y1 < 0 || map.layout[y1][x1] == '\0')
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
		direction = player.direction + atan((i - GAME_FINENESS / 2) * 2 * tan(GAME_FOV / 2) / GAME_FINENESS);
		ray_distance_array[i] = calculate_ray_distance(map, player.x, player.y, direction);
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
