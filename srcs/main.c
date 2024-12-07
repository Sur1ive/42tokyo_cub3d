/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42tokyo.jp>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 22:22:15 by yxu               #+#    #+#             */
/*   Updated: 2024/12/01 13:00:26 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_game	game;

	argv_checker(argc, argv);
	init_game(argv[1], &game);
	mlx_key_hook(game.win, key_handler, &game);
	mlx_hook(game.win, 17, (1L << 0), close_win_handler, &game);
	mlx_loop_hook(game.mlx, screenctl, &game);
	mlx_loop(game.mlx);
	clean_exit(RUN_ERR, "mlx err", &game);
}
