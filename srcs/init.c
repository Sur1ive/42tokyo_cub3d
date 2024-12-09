/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             ::      ::    ::   */
/*                                                    : :         :     */
/*   By: nakagawashinta <nakagawashinta@student.    #  :       #        */
/*                                                #####   #           */
/*   Created: 2023/12/19 16:49:56 by yxu               ##    ##             */
/*   Updated: 2024/12/03 23:46:10 by nakagawashi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fill_map(char **map, int cols);
int		get_max_cols(char **layout);

static void	game_preset(t_game *game)
{
	game->mlx = NULL;
	game->win = NULL;
	game->map.layout = NULL;
	game->map.elements = NULL;
	game->map.floor_color = create_trgb(0, 99, 62, 0);
	game->map.ceiling_color = create_trgb(0, 102, 170, 255);
}

static void	get_floor_ceiling_colors(char **type, char **color, t_map *map)
{
	char	**rgb;
	int		**n_rgb;
	int		i;

	rgb = ft_split(color, ',');
	if (!rgb)
		return ;
	i = 0;
	while (rgb[i])
	{
		n_rgb[i] = ft_atoi(rgb[i]);
		i++;
	}
	if (!ft_strcmp(type, "F"))
		map->floor_color = create_trgb(0, n_rgb[0], n_rgb[1], n_rgb[2]);
	else
		map->ceiling_color = create_trgb(0, n_rgb[0], n_rgb[1], n_rgb[2]);
}

static void	map_elements_set(char *path, t_game *game)
{
	int		fd;
	char	**split;
	char	*line;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		clean_exit(2, "Map loading error\n", game);
	line = get_next_line(fd);
	while (line)
	{
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		if (is_element(line))
		{
			split = ft_split(line, ' ');
			if (ft_strchr("NSEW", split[0][0]))
				load_texture(game, split[1], (unsigned char *)split[0]);
			else
				get_floor_ceiling_colors(split[0], split[1], game->map);
			free2(split);
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

static double	get_player_direciotion(char direction)
{
	if (direction == 'N')
		return (3 / 2 * PI);
	else if (direction == 'S')
		return (1 / 2 * PI);
	else if (direction == 'E')
		return (0);
	else if (direction == 'W')
		return (PI);
	return (-1);
}

static void	init_player(t_game *game)
{
	int		i;
	int		j;

	j = 0;
	while (game->map.layout[j])
	{
		i = 0;
		while (game->map.layout[j][i])
		{
			if (ft_strchr("NSEW", game->map.layout[j][i]))
				break ;
			i++;
		}
		if (game->map.layout[j][i] && ft_strchr("NSEW", game->map.layout[j][i]))
			break ;
		j++;
	}
	game->player.x = i + 0.5;
	game->player.y = j + 0.5;
	game->player.direction = get_player_direciotion(game->map.layout[j][i]);
}

static void	init_map_and_player(char *map_path, t_game *game)
{
	map_elements_set(map_path, game);
	game->map.rows = count_line(map_path);
	game->map.layout = read_map(map_path, game);
	game->map.cols = get_max_cols(game->map.layout);
	init_player(game);
	fill_map(game->map.layout, game->map.cols);
	print_layout(game->map.layout);
	check_map(game);
}

void	init_game(char *map_path, t_game *game)
{
	game_preset(game);
	game->mlx = mlx_init();
	if (game->mlx == NULL)
		clean_exit(INIT_ERR, "MLX initialization failed", game);
	game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3d");
	if (game->win == NULL)
		clean_exit(INIT_ERR, "MLX initialization failed", game);
	init_map_and_player(map_path, game);
}
