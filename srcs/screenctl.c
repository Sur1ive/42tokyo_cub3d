/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenctl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42tokyo.jp>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 22:41:58 by yxu               #+#    #+#             */
/*   Updated: 2024/12/01 16:21:20 by yxu              ###   ########.fr       */
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

	dst = image->addr + (y * image->line_length + x * (image->bits_per_pixel / 8));
	*(int *)dst = color;
}

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

int	screenctl(t_game *game)
{
	t_image	frame;

	frame.img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	frame.addr = mlx_get_data_addr(frame.img, &frame.bits_per_pixel,
			&frame.line_length, &frame.endian);
	draw_background(&frame, game->map.floor_color, game->map.ceiling_color);
	mlx_put_image_to_window(game->mlx, game->win, frame.img, 0, 0);
	// mlx_put_image_to_window(game->mlx, game->win,
	// 			get_texture_with_id(game, EID_WALL_E), 0, 0);
	mlx_destroy_image(game->mlx, frame.img);
	return (0);
}
