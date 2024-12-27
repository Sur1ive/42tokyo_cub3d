/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakagawashinta <nakagawashinta@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 15:52:07 by yxu               #+#    #+#             */
/*   Updated: 2024/12/28 02:10:09 by nakagawashi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	check_map_obj(char **layout)
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
			if (!ft_strchr("01NSEW \n", layout[x][y])
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

static bool	floodfill(t_game *game, char **filled_map, int x, int y)
{
	bool	is_surrounded;

	if (x < 0 || y < 0 || game->map.rows <= y || game->map.cols <= x)
		return (false);
	if (filled_map[y][x] == '1')
		return (true);
	if (filled_map[y][x] != '0')
		return (true);
	filled_map[y][x] = '*';
	is_surrounded = true;
	is_surrounded &= floodfill(game, filled_map, x + 1, y);
	is_surrounded &= floodfill(game, filled_map, x - 1, y);
	is_surrounded &= floodfill(game, filled_map, x, y + 1);
	is_surrounded &= floodfill(game, filled_map, x, y - 1);
	return (is_surrounded);
}

static int	check_map_wall(t_game *game, char **layout)
{
	char	**filled_map;
	int		i;
	bool	is_surrounded;
	int		x;
	int		y;

	filled_map = malloc((game->map.rows + 1) * sizeof(char *));
	i = 0;
	x = game->player.location.x;
	y = game->player.location.y;
	while (i < game->map.rows)
	{
		filled_map[i] = ft_strdup(layout[i]);
		i++;
	}
	filled_map[i] = NULL;
	filled_map[y][x] = '0';
	is_surrounded = floodfill(game, filled_map, x, y);
	free2(filled_map);
	if (is_surrounded)
		return (1);
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
	if (!check_map_wall(game, map.layout))
		clean_exit(INIT_ERR, "Map is not closed/surrounded by wall", game);
}
