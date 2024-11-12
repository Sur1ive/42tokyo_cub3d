/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42tokyo.jp>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 21:29:33 by yxu               #+#    #+#             */
/*   Updated: 2024/11/12 22:48:40 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// static void	check_map_load(char **map, t_game *game)
// {
// 	int	i;
// 	int	rows;

// 	i = 0;
// 	rows = game->map.rows;
// 	if (rows == 0)
// 	{
// 		free_map(map);
// 		clean_exit(2, "Map loading error\n", NULL);
// 	}
// 	while (rows-- > 0)
// 	{
// 		if (map[i++] == NULL)
// 		{
// 			free_map(map);
// 			clean_exit(2, "Map loading error\n", NULL);
// 		}
// 	}
// }

char	**read_map(char *path, t_game *game)
{
	// int		fd;
	// char	**map;
	// int		i;

	// fd = open(path, O_RDONLY);
	// if (fd == -1)
	// 	clean_exit(2, "Map loading error\n", game);
	// map = (char **)malloc(sizeof(char *) * (game->map.rows + 1));
	// if (map == NULL)
	// {
	// 	close(fd);
	// 	clean_exit(2, "Map loading error\n", game);
	// }
	// map[game->map.rows] = game;
	// i = 0;
	// while (i < game->map.rows)
	// 	map[i++] = get_next_line(fd);
	// close(fd);
	// check_map_load(map, game);
	// i--;
	// while (--i >= 0)
	// 	map[i][ft_strlen(map[i]) - 1] = '\0';
	// return (map);
	(void)game;
	(void)path;
	return (NULL);
}
