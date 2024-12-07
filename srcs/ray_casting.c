/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 22:41:58 by yxu               #+#    #+#             */
/*   Updated: 2024/12/07 19:57:30 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	intersection_is_wall(t_map map, double x, double y
	, double direction)
{
	int		x1;
	int		y1;

	if (floor(x) == x && floor(y) == y)
	{
		x1 = x;
		y1 = y;
		if (map.layout[y1 - 1][x1] == '1' || map.layout[y1][x1 - 1] == '1'
		|| map.layout[y1][x1] == '1' || map.layout[y1 - 1][x1 - 1] == '1')
			return (1);
		else
			return (0);
	}
	if (floor(x) == x)
	{
		y1 = floor(y);
		if (direction > PI / 2 && direction < PI * 3 / 2)
			x1 = x - 1;
		else
			x1 = x;
	}
	else
	{
		x1 = floor(x);
		if (direction > PI)
			y1 = y - 1;
		else
			y1 = y;
	}
	if (map.layout[y1][x1] == '1')
		return (1);
	else
		return (0);
}

double	calculate_ray_distance(t_map map, double origin_x, double origin_y,
	double direction)
{
	double	x;
	double	y;

	direction = limit_angle(direction);
	x = origin_x;
	y = origin_y;
	while (1)
	{
		to_next_intersection(&x, &y, direction);
		if (intersection_is_wall(map, x, y, direction))
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
		direction = player.direction + atan(\
			(i - GAME_FINENESS / 2) * 2 * tan(GAME_FOV / 2) / GAME_FINENESS);
		ray_distance_array[i] = \
			calculate_ray_distance(map, player.x, player.y, direction);
		i++;
	}
	return (ray_distance_array);
}
