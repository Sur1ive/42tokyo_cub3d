/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42tokyo.jp>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 15:52:07 by yxu               #+#    #+#             */
/*   Updated: 2024/12/01 14:48:38 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	check_map_obj(char **layout)
{
	int		x;
	int		y;
	char	spawn_direction;

	x = 0;
	spawn_direction = '\0';
	while (layout[x])
	{
		y = 0;
		while (layout[x][y])
		{
			if (!ft_strchr("01NSEW", layout[x][y])
				|| (ft_strchr("NSEW", layout[x][y]) && spawn_direction))
				return ('\0');
			if (ft_strchr("NSEW", layout[x][y]) && !spawn_direction)
				spawn_direction = layout[x][y];
			y++;
		}
		x++;
	}
	return (spawn_direction);
}

static int	check_map_wall(char **layout, int rows)
{
	(void)layout;
	(void)rows;
	return (0);
}

void	check_map(t_game *game)
{
	t_map	map;

	map = game->map;
	if (map.rows > MAX_MAP_ROWS || map.cols > MAX_MAP_COLS)
		clean_exit(INIT_ERR, "Map is too large", game);
	if (!check_map_obj(map.layout))
		clean_exit(INIT_ERR, "Map must be composed of 01NSEW", game);
	if (check_map_wall(map.layout, map.rows))
		clean_exit(INIT_ERR, "Map is not closed/surrounded by wall", game);
}
