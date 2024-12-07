/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 22:41:58 by yxu               #+#    #+#             */
/*   Updated: 2024/12/07 18:53:14 by yxu              ###   ########.fr       */
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

static char	intersection_direction(double *x, double *y, double k,
	double direction)
{
	double	dx;
	double	dy;

	dx = floor(*x + 1) - *x;
	dy = floor(*y + 1) - *y;
	if (direction > PI / 2 && direction < PI * 3 / 2)
		dx = 1 - dx;
	if (direction > PI)
		dy = 1 - dy;
	if (dy < fabs(k * dx))
	{
		if (direction > PI)
			return ('N');
		else
			return ('S');
	}
	else
	{
		if (direction > PI / 2 && direction < PI * 3 / 2)
			return ('W');
		else
			return ('E');
	}
}

static void	compute_next_intersection(double *x, double *y, double k,
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
