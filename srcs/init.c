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

static void	game_preset(t_game *game)
{
	game->mlx = NULL;
	game->win = NULL;
	game->map.layout = NULL;
	game->map.elements = NULL;
}

static int	map_elements_set(char *path, t_game *game)
{
	int		fd;
	char	**split;
	char	*line;
	t_map	*map;

	map = &(game->map);
	fd = open(path, O_RDONLY);
	if (fd == -1)
			return (-1);
	line = get_next_line(fd);
	if (line[ft_strlen(line) -1] == '\n')
		line[ft_strlen(line) - 1] = '\0';
	while (line)
	{
		if (is_element(line))
		{
			split = ft_split(line, ' ');			
			if (ft_strchr("NSEW", split[0][0]))
				load_texture(game, split[1], (unsigned char*)split[0]);
			else if (split[0][0] == 'F')
				map->floor_color = create_trgb(0,255,255,255);
			else
				map->ceiling_color = create_trgb(0,1,1,1);
		}
		line = get_next_line(fd);
		if (line && line[ft_strlen(line) -1] == '\n')
		line[ft_strlen(line) - 1] = '\0';
	}
	close(fd);
	return (1);
}

static void	init_map_and_player(char *map_path, t_game *game)
{
	map_elements_set(map_path, game);
	game->map.rows = count_line(map_path);
	game->map.layout = read_map(map_path, game);
	print_layout(game->map.layout);
	check_map(game);
	clean_exit(INIT_ERR, NULL, game);
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
