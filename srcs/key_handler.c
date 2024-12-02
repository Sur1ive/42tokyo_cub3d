/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42tokyo.jp>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 18:01:27 by yxu               #+#    #+#             */
/*   Updated: 2024/12/02 21:47:19 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "key_linux.h"

// void	player_move(t_map map, t_player player)
// {


// }

int	key_handler(int key, t_game *game)
{
	if (key == K_ESC)
		clean_exit(MANUAL_QUIT, "Manual exit\n", game);
	// if (key == K_W)
	// 	game->player.x += 0.1;
	// if (key == K_W || key == K_A || key == K_S || key == K_D)
	// {
	// 	player_move(key);
	// }
	if (key == K_AR_L)
		game->player.direction = limit_angle(game->player.direction - 0.1);
	if (key == K_AR_R)
		game->player.direction = limit_angle(game->player.direction + 0.1);
	return (0);
}
