/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42tokyo.jp>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 22:22:15 by yxu               #+#    #+#             */
/*   Updated: 2024/11/12 22:45:04 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_game	game;

	argv_checker(argc, argv);
	init_game(argv[1], &game);
	mlx_key_hook(game.win, key_handler, &game);
	mlx_hook(game.win, 17, (1L << 0), destory_win, &game);
	mlx_loop_hook(game.mlx, screenctl, &game);
	mlx_loop(game.mlx);
	clean_exit(ERR, "mlx err", &game);
}
