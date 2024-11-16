/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42tokyo.jp>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 16:49:56 by yxu               #+#    #+#             */
/*   Updated: 2024/11/16 19:34:12 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	game_preset(t_game *game)
{
	game->mlx = NULL;
	game->win = NULL;
	game->map.layout = NULL;
	game->map.elements = NULL;
}

// static int	load_textures(t_game *game)
// {
// 	game->textures.wall_n.img = mlx_xpm_file_to_image(game->mlx,
// 			"textures/wall_n.xpm",
// 			&game->textures.wall_n.width, &game->textures.wall_n.height);
// 	return (0);
// }

static void	init_map_and_player(char *map_path, t_game *game)
{
	game->map.rows = count_line(map_path);
	game->map.layout = read_map(map_path, game);
	check_map(game);
}

void	init_game(char *map_path, t_game *game)
{
	game_preset(game);
	init_map_and_player(map_path, game);
	game->mlx = mlx_init();
	if (game->mlx == NULL)
		clean_exit(ERR, "MLX initialization failed", game);
	game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3d");
	if (game->win == NULL)
		clean_exit(ERR, "MLX initialization failed", game);
}
