/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42tokyo.jp>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 22:41:58 by yxu               #+#    #+#             */
/*   Updated: 2024/12/08 17:29:28 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_point	get_wall_location(t_point p, char intersection_direction)
{
	t_point	wall;

	if (floor(p.x) == p.x && floor(p.y) == p.y)
	{
		wall.x = p.x;
		wall.y = p.y;
	}
	else if (floor(p.x) == p.x)
	{
		wall.y = floor(p.y);
		if (intersection_direction == 'W')
			wall.x = p.x - 1;
		else
			wall.x = p.x;
	}
	else
	{
		wall.x = floor(p.x);
		if (intersection_direction == 'N')
			wall.y = p.y - 1;
		else
			wall.y = p.y;
	}
	return (wall);
}

static int	intersection_is_wall(t_map map, t_point p
	, char intersection_direction)
{
	t_point	wall;
	int		x;
	int		y;

	wall = get_wall_location(p, intersection_direction);
	x = wall.x;
	y = wall.y;
	if (floor(p.x) == p.x && floor(p.y) == p.y)
	{
		if (map.layout[y - 1][x] == '1' || map.layout[y][x - 1] == '1'
		|| map.layout[y][x] == '1' || map.layout[y - 1][x - 1] == '1')
			return (1);
		else
			return (0);
	}
	else if (map.layout[y][x] == '1')
		return (1);
	else
		return (0);
}

static void	calculate_ray_casting(t_map map, t_ray *ray)
{
	ray->tail = ray->origin;
	while (1)
	{
		to_next_intersection(ray);
		if (intersection_is_wall(map, ray->tail, ray->intersection_direction))
		{
			ray->distance = sqrt(
					pow(ray->tail.x - ray->origin.x, 2)
					+ pow(ray->tail.y - ray->origin.y, 2));
			return ;
		}
	}
}

t_ray	*ray_casting(t_map map, t_player player)
{
	t_ray	*ray_array;
	int		i;
	double	angle;

	ray_array = (t_ray *)malloc(sizeof(t_ray) * FINENESS);
	if (ray_array == NULL)
		return (NULL);
	i = 0;
	while (i < FINENESS)
	{
		angle = atan((i - FINENESS / 2) * 2 * tan(FOV / 2) / FINENESS);
		ray_array[i].direction = limit_angle(player.direction + angle);
		ray_array[i].origin = player.location;
		calculate_ray_casting(map, &ray_array[i]);
		i++;
	}
	return (ray_array);
}
