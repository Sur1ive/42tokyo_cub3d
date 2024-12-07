/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 22:41:58 by yxu               #+#    #+#             */
/*   Updated: 2024/12/07 19:06:21 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// static int	intersection_is_wall()
// {



// }

double	calculate_ray_distance(t_map map, double origin_x, double origin_y, double direction)
{
	double	x;
	double	y;
	int		x1;
	int		y1;

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
		direction = player.direction + atan(\
			(i - GAME_FINENESS / 2) * 2 * tan(GAME_FOV / 2) / GAME_FINENESS);
		ray_distance_array[i] = \
			calculate_ray_distance(map, player.x, player.y, direction);
		i++;
	}
	return (ray_distance_array);
}
