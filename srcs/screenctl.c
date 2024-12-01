/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenctl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42tokyo.jp>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 22:41:58 by yxu               #+#    #+#             */
/*   Updated: 2024/12/01 14:09:05 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	screenctl(t_game *game)
{
	mlx_put_image_to_window(game->mlx, game->win,
				get_texture_with_id(game, EID_WALL_E), 0, 0);
	return (0);
}
