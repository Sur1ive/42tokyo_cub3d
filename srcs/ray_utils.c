/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 22:41:58 by yxu               #+#    #+#             */
/*   Updated: 2025/01/01 15:02:42 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	offset_from_gridline(double *x, double *y, double direction)
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

static char	compute_intersection_direction(double x, double y, double k,
	double direction)
{
	double	dx;
	double	dy;

	dx = floor(x + 1) - x;
	dy = floor(y + 1) - y;
	if (direction > PI / 2 && direction < PI * 3 / 2)
		dx = 1 - dx;
	if (direction > PI)
		dy = 1 - dy;
	if (dy < fabs(k * dx))
	{
		if (direction > PI)
			return ('S');
		else
			return ('N');
	}
	else
	{
		if (direction > PI / 2 && direction < PI * 3 / 2)
			return ('E');
		else
			return ('W');
	}
}

static void	compute_next_intersection(double *x, double *y, double k,
	char intersection_direction)
{
	const double	origin_x = *x;
	const double	origin_y = *y;

	if (intersection_direction == 'S')
	{
		*y = ceil(*y - 1);
		*x = origin_x + (*y - origin_y) / k;
	}
	if (intersection_direction == 'N')
	{
		*y = floor(*y + 1);
		*x = origin_x + (*y - origin_y) / k;
	}
	if (intersection_direction == 'E')
	{
		*x = ceil(*x - 1);
		*y = origin_y + (*x - origin_x) * k;
	}
	if (intersection_direction == 'W')
	{
		*x = floor(*x + 1);
		*y = origin_y + (*x - origin_x) * k;
	}
}

void	to_next_intersection(t_ray *ray)
{
	const double	k = tan(ray->direction);

	offset_from_gridline(&ray->tail.x, &ray->tail.y, ray->direction);
	ray->intersection_direction
		= compute_intersection_direction(
			ray->tail.x, ray->tail.y, k, ray->direction);
	compute_next_intersection(
		&ray->tail.x, &ray->tail.y, k, ray->intersection_direction);
}
