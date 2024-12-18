/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42tokyo.jp>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 22:08:17 by yxu               #+#    #+#             */
/*   Updated: 2024/12/18 23:48:01 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	ft_mlx_pixel_put(t_image *image, int x, int y, int color)
{
	char	*dst;

	dst = image->addr
		+ y * image->line_length + x * (image->bits_per_pixel / 8);
	*(int *)dst = color;
}

int	ft_mlx_get_image_pixel(t_image *image, double x_ratio, double y_ratio)
{
	char	*dst;
	int		x;
	int		y;

	x = x_ratio * (image->width - 1);
	y = y_ratio * (image->height - 1);
	dst = image->addr
		+ y * image->line_length + x * (image->bits_per_pixel / 8);
	return (*(int *)dst);
}
