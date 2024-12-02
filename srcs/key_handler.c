/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42tokyo.jp>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 18:01:27 by yxu               #+#    #+#             */
/*   Updated: 2024/12/03 02:07:59 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "key_linux.h"

t_player	player_move(t_player player, int key)
{
	if (key == K_W)
	{
		player.x += cos(player.direction) * MOVE_SPEED;
		player.y += sin(player.direction) * MOVE_SPEED;
	}
	if (key == K_S)
	{
		player.x -= cos(player.direction) * MOVE_SPEED;
		player.y -= sin(player.direction) * MOVE_SPEED;
	}
	if (key == K_A)
	{
		player.x += sin(player.direction) * MOVE_SPEED;
		player.y -= cos(player.direction) * MOVE_SPEED;
	}
	if (key == K_D)
	{
		player.x -= sin(player.direction) * MOVE_SPEED;
		player.y += cos(player.direction) * MOVE_SPEED;
	}
	return (player);
}

t_player	limit_move(t_map map, t_player player)
{
	double	x;
	double	y;

	x = player.x;
	y = player.y;
	if (map.layout[(int)y][(int)round(x)] == '1' && fabs(x - round(x)) < PLAYER_SIZE)
	{
		if (x > round(x))
			player.x = round(x) + PLAYER_SIZE;
		else
			player.x = round(x) - PLAYER_SIZE;
	}
	if (map.layout[(int)round(y)][(int)x] == '1' && fabs(y - round(y)) < PLAYER_SIZE)
	{
		if (y > round(y))
			player.y = round(y) + PLAYER_SIZE;
		else
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
		game->player.direction = limit_angle(game->player.direction - 0.1);
	if (key == K_AR_R)
		game->player.direction = limit_angle(game->player.direction + 0.1);
	return (0);
}
