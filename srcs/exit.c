/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42tokyo.jp>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 21:35:16 by yxu               #+#    #+#             */
/*   Updated: 2024/11/12 22:23:08 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_game(t_game *game)
{
	(void)game;
}

void	clean_exit(int exitcode, char *errmsg, t_game *game)
{
	free_game(game);
	if (exitcode == MANUAL_QUIT)
	{
		printf("Manual quit\n");
		exit(EXIT_SUCCESS);
	}
	else
	{
		ft_dprintf(STDERR_FILENO, "Error\n%s\n", errmsg);
		exit(EXIT_FAILURE);
	}
}

int	destory_win(t_game *game)
{
	clean_exit(MANUAL_QUIT, "Manual exit\n", game);
	return (0);
}
