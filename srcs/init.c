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

void	fill_map(char **map, int cols, t_game *game);
int		get_max_cols(char **layout);

static void	game_preset(t_game *game)
{
	game->mlx = NULL;
	game->win = NULL;
	game->map.layout = NULL;
	game->map.elements = NULL;
	game->map.floor_color = 0;
	game->map.ceiling_color = 0;
}

static void	get_floor_ceiling_colors(char *type, char *color, t_map *map)
{
	char	**rgb;
	int		n_rgb[3];
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
	free2(rgb);
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
				get_floor_ceiling_colors(split[0], split[1], &(game->map));
			free2(split);
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

static void	init_map_and_player(char *map_path, t_game *game)
{
	map_elements_set(map_path, game);
	game->map.rows = count_line(map_path);
	game->map.layout = read_map(map_path, game);
	game->map.cols = get_max_cols(game->map.layout);
	init_player(game);
	check_map(game);
	fill_map(game->map.layout, game->map.cols, game);
	print_layout(game->map.layout);
}

void	init_game(char *map_path, t_game *game)
{
	game_preset(game);
	game->mlx = mlx_init();
	if (game->mlx == NULL)
		clean_exit(INIT_ERR, "MLX initialization failed", game);
	load_texture(game, "textures/Textures-1.xpm", EID_WALL_N);
	load_texture(game, "textures/Textures-2.xpm", EID_WALL_S);
	load_texture(game, "textures/Textures-3.xpm", EID_WALL_W);
	load_texture(game, "textures/Textures-4.xpm", EID_WALL_E);
	game->map.floor_color = create_trgb(0, 99, 62, 0);
	game->map.ceiling_color = create_trgb(0, 137, 189, 222);
	game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3d");
	if (game->win == NULL)
		clean_exit(INIT_ERR, "MLX initialization failed", game);
	init_map_and_player(map_path, game);
}
