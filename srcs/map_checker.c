/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42tokyo.jp>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 15:52:07 by yxu               #+#    #+#             */
/*   Updated: 2024/11/12 00:22:56 by yxu              ###   ########.fr       */
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

static int	check_map_rectangular(char **map)
{
	int		i;
	size_t	row_length;

	row_length = ft_strlen(map[0]);
	i = 1;
	while (map[i])
		if (ft_strlen(map[i++]) != row_length)
			return (-1);
	return (0);
}

static int	check_map_wall(char **map, int rows)
{
	int	x;
	int	y;
	int	cols;

	cols = ft_strlen(map[0]);
	x = 0;
	while (map[x])
	{
		y = 0;
		while (map[x][y])
		{
			if (x == 0 || y == 0 || x == rows - 1 || y == cols - 1)
				if (map[x][y] != '1')
					return (-1);
			y++;
		}
		x++;
	}
	return (0);
}

void	check_map(t_data *data)
{
	if (data->rows > MAX_MAP_ROWS || data->cols > MAX_MAP_COLS)
		clean_exit(ERR, "Map is too large", data);
	if (!check_map_obj(data->map))
		clean_exit(ERR, "Map must be composed of 01NSEW", data);
	if (check_map_rectangular(data->map))
		clean_exit(ERR, "Map is not rectangular", data);
	if (check_map_wall(data->map, data->rows))
		clean_exit(ERR, "Map is not closed/surrounded by wall", data);
}
