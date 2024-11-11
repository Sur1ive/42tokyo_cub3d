/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42tokyo.jp>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 17:04:34 by yxu               #+#    #+#             */
/*   Updated: 2024/11/12 00:30:22 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	count_line(char *path)
{
	int		fd;
	int		nb;
	char	*line;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (-1);
	nb = 0;
	line = get_next_line(fd);
	while (line)
	{
		nb++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (nb);
}

void	check_map_load(char **map, t_data *data)
{
	int	i;
	int	rows;

	i = 0;
	rows = data->rows;
	if (rows == 0)
	{
		free_map(map);
		clean_exit(2, "Map loading error\n", NULL);
	}
	while (rows-- > 0)
	{
		if (map[i++] == NULL)
		{
			free_map(map);
			clean_exit(2, "Map loading error\n", NULL);
		}
	}
}

char	**read_map(char *path, t_data *data)
{
	int		fd;
	char	**map;
	int		i;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		clean_exit(2, "Map loading error\n", NULL);
	map = (char **)malloc(sizeof(char *) * (data->rows + 1));
	if (map == NULL)
	{
		close(fd);
		clean_exit(2, "Map loading error\n", NULL);
	}
	map[data->rows] = NULL;
	i = 0;
	while (i < data->rows)
		map[i++] = get_next_line(fd);
	close(fd);
	check_map_load(map, data);
	i--;
	while (--i >= 0)
		map[i][ft_strlen(map[i]) - 1] = '\0';
	return (map);
}

int	print_map(char **map)
{
	int	x;

	if (map == NULL)
		return (0);
	x = 0;
	while (map[x])
	{
		ft_printf("%s\n", map[x]);
		x++;
	}
	ft_printf("\n");
	return (0);
}

int	free_map(char **map)
{
	int	x;

	if (map == NULL)
		return (0);
	x = 0;
	while (map[x])
	{
		free(map[x]);
		x++;
	}
	free(map);
	return (0);
}
