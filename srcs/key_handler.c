/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 18:01:27 by yxu               #+#    #+#             */
/*   Updated: 2024/12/07 20:04:55 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "key_linux.h"

t_player	player_move(t_player player, int key)
{
	double	direction;

	direction = player.direction;
	if (key == K_W)
		direction += 0;
	if (key == K_S)
		direction += PI;
	if (key == K_A)
		direction += PI * 3 / 2;
	if (key == K_D)
		direction += PI / 2;
	player.x += cos(direction) * MOVE_SPEED;
	player.y += sin(direction) * MOVE_SPEED;
	return (player);
}

t_player	limit_move(t_map map, t_player player)
{
	double	x;
	double	y;

	x = player.x;
	y = player.y;
	if (fabs(x - round(x)) < PLAYER_SIZE)
	{
		if (x > round(x) && map.layout[(int)y][(int)round(x) - 1] == '1')
			player.x = round(x) + PLAYER_SIZE;
		else if (x < round(x) && map.layout[(int)y][(int)round(x)] == '1')
			player.x = round(x) - PLAYER_SIZE;
	}
	if (fabs(y - round(y)) < PLAYER_SIZE)
	{
		if (y > round(y) && map.layout[(int)round(y) - 1][(int)x] == '1')
			player.y = round(y) + PLAYER_SIZE;
		else if (y < round(y) && map.layout[(int)round(y)][(int)x] == '1')
			player.y = round(y) - PLAYER_SIZE;
	}
	return (player);
}

int	key_handler(int key, t_game *game)
{
	t_player	player;

	player = game->player;
	if (key == K_ESC)
		clean_exit(MANUAL_QUIT, "Manual exit\n", game);
	if (key == K_W || key == K_A || key == K_S || key == K_D)
	{
		player = player_move(player, key);
		game->player = limit_move(game->map, player);
	}
	if (key == K_AR_L)
		game->player.direction = limit_angle(
				game->player.direction - CAMERA_TURN_SPEED);
	if (key == K_AR_R)
		game->player.direction = limit_angle(
				game->player.direction + CAMERA_TURN_SPEED);
	return (0);
}
