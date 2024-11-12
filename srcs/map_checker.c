/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42tokyo.jp>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 15:52:07 by yxu               #+#    #+#             */
/*   Updated: 2024/11/12 22:47:09 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	check_map_obj(char **map)
{
	int		x;
	int		y;
	char	spawn_orientation;

	x = 0;
	spawn_orientation = '\0';
	while (map[x])
	{
		y = 0;
		while (map[x][y])
		{
			if (!ft_strchr("01NSEW", map[x][y])
				|| (ft_strchr("NSEW", map[x][y]) && spawn_orientation))
				return ('\0');
			if (ft_strchr("NSEW", map[x][y]) && !spawn_orientation)
				spawn_orientation = map[x][y];
			y++;
		}
		x++;
	}
	return (spawn_orientation);
}

static int	check_map_wall(char **map, int rows)
{
	// int	x;
	// int	y;
	// int	cols;

	// cols = ft_strlen(map[0]);
	// x = 0;
	// while (map[x])
	// {
	// 	y = 0;
	// 	while (map[x][y])
	// 	{
	// 		if (x == 0 || y == 0 || x == rows - 1 || y == cols - 1)
	// 			if (map[x][y] != '1')
	// 				return (-1);
	// 		y++;
	// 	}
	// 	x++;
	// }
	(void)map;
	(void)rows;
	return (0);
}

void	check_map(t_game *game)
{
	t_map	map;

	map = game->map;
	if (map.rows > MAX_MAP_ROWS || map.cols > MAX_MAP_COLS)
		clean_exit(ERR, "Map is too large", game);
	if (!check_map_obj(map.content))
		clean_exit(ERR, "Map must be composed of 01NSEW", game);
	if (check_map_wall(map.content, map.rows))
		clean_exit(ERR, "Map is not closed/surrounded by wall", game);
}
