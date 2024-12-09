/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakagawashinta <nakagawashinta@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 21:29:33 by yxu               #+#    #+#             */
/*   Updated: 2024/12/09 13:39:28 by nakagawashi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fill_map(char **map, int cols)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = ft_strlen(map[i]);
		while (j < cols)
		{
			map[i][j] = '1';
			j++;
		}
		map[i][j] = '\0';
		i++;
	}
}

static void	check_map_load(char **map, t_game *game)
{
	int	i;
	int	rows;

	i = 0;
	rows = game->map.rows;
	if (rows == 0)
	{
		free_map(game);
		clean_exit(2, "Map loading error\n", NULL);
	}
	while (rows-- > 0)
	{
		if (map[i++] == NULL)
		{
			free_map(game);
			clean_exit(2, "Map loading error\n", NULL);
		}
	}
}

int	get_max_cols(char **layout)
{
	size_t	cols;
	int		i;

	i = 0;
	cols = 0;
	while (layout[i])
	{
		if (cols < ft_strlen(layout[i]))
			cols = ft_strlen(layout[i]);
		i++;
	}
	return (cols);
}

static char	**load_map_layout(int fd, t_game *game)
{
	char	**map;
	char	*line;
	int		i;

	map = (char **)malloc(sizeof(char *) * (game->map.rows + 1));
	if (!map)
		return (NULL);
	map[game->map.rows] = NULL;
	line = get_next_line(fd);
	while (line && (is_element(line) || line[0] == '\n'))
	{
		free(line);
		line = get_next_line(fd);
	}
	i = 0;
	while (i < game->map.rows)
	{
		map[i++] = line;
		line = get_next_line(fd);
	}
	free(line);
	return (map);
}

char	**read_map(char *path, t_game *game)
{
	int		fd;
	char	**map;
	int		i;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		clean_exit(2, "Map loading error\n", game);
	map = load_map_layout(fd, game);
	if (map == NULL)
	{
		close(fd);
		clean_exit(2, "Map loading error\n", game);
	}
	close(fd);
	check_map_load(map, game);
	i = game->map.rows;
	while (--i >= 0)
		map[i][ft_strlen(map[i]) - 1] = '\0';
	return (map);
}
