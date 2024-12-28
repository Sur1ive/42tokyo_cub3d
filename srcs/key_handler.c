/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42tokyo.jp>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 18:01:27 by yxu               #+#    #+#             */
/*   Updated: 2024/12/25 00:05:27 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "key_linux.h"

static t_player	player_move(t_player player, int key)
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
	player.location.x += cos(direction) * MOVE_SPEED;
	player.location.y += sin(direction) * MOVE_SPEED;
	return (player);
}

static t_player	limit_move(t_map map, t_player player)
{
	double	x;
	double	y;

	x = player.location.x;
	y = player.location.y;
	if (fabs(x - round(x)) < PLAYER_SIZE)
	{
		if (x > round(x) && map.layout[(int)y][(int)round(x) - 1] == '1')
			player.location.x = round(x) + PLAYER_SIZE;
		else if (x < round(x) && map.layout[(int)y][(int)round(x)] == '1')
			player.location.x = round(x) - PLAYER_SIZE;
	}
	if (fabs(y - round(y)) < PLAYER_SIZE)
	{
		if (y > round(y) && map.layout[(int)round(y) - 1][(int)x] == '1')
			player.location.y = round(y) + PLAYER_SIZE;
		else if (y < round(y) && map.layout[(int)round(y)][(int)x] == '1')
			player.location.y = round(y) - PLAYER_SIZE;
	}
	return (player);
}

static t_player	limit_move_corner(t_map map, t_player player)
{
	double	x;
	double	y;
	int		near_e;
	int		near_s;

	x = player.location.x;
	y = player.location.y;
	if (fabs(x - round(x)) < PLAYER_SIZE && fabs(y - round(y)) < PLAYER_SIZE)
	{
		near_e = 0;
		near_s = 0;
		if (x < round(x))
			near_e = 1;
		if (y < round(y))
			near_s = 1;
		if (map.layout[(int)round(y) - 1 + near_s][(int)round(x) - 1 + near_e]
			== '1')
		{
			if (fabs(x - round(x)) > fabs(y - round(y)))
				player.location.x = round(x) + PLAYER_SIZE * (1 - 2 * near_e);
			else
				player.location.y = round(y) + PLAYER_SIZE * (1 - 2 * near_s);
		}
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
		player = limit_move(game->map, player);
		player = limit_move_corner(game->map, player);
		game->player = player;
	}
	if (key == K_AR_L)
		game->player.direction = limit_angle(
				game->player.direction - CAMERA_TURN_SPEED);
	if (key == K_AR_R)
		game->player.direction = limit_angle(
				game->player.direction + CAMERA_TURN_SPEED);
	return (0);
}
