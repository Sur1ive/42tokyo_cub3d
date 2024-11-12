/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42tokyo.jp>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 16:49:56 by yxu               #+#    #+#             */
/*   Updated: 2024/11/12 22:46:40 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	game_preset(t_game *game)
{
	(void)game;
}

static int	load_textures(t_game *game)
{
	game->textures.wall_n.content = mlx_xpm_file_to_image(game->mlx,
			"textures/wall_n.xpm",
			&game->textures.wall_n.width, &game->textures.wall_n.height);
	game->textures.wall_s.content = mlx_xpm_file_to_image(game->mlx,
			"textures/wall_s.xpm",
			&game->textures.wall_s.width, &game->textures.wall_s.height);
	game->textures.wall_w.content = mlx_xpm_file_to_image(game->mlx,
			"textures/wall_w.xpm",
			&game->textures.wall_w.width, &game->textures.wall_w.height);
	game->textures.wall_e.content = mlx_xpm_file_to_image(game->mlx,
			"textures/wall_e.xpm",
			&game->textures.wall_e.width, &game->textures.wall_e.height);
	return (0);
}

void	init_game(char *map_path, t_game *game)
{
	game_preset(game);
	game->map.rows = count_line(map_path);
	game->map.content = read_map(map_path, game);
	check_map(game);
	load_textures(game);
	game->mlx = mlx_init();
	if (game->mlx == NULL)
		clean_exit(ERR, "MLX initialization failed", game);
	game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3d");
}
