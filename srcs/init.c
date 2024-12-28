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
void	change_space_to_zero(t_map *map);
int		check_elements(char *map_path, t_game *game);
void	map_elements_set(char *path, t_game *game);

static void	game_preset(t_game *game)
{
	game->mlx = NULL;
	game->win = NULL;
	game->map.layout = NULL;
	game->map.elements = NULL;
	game->map.floor_color = 0;
	game->map.ceiling_color = 0;
}

int	is_element(char *line)
{
	if (!line)
		return (-1);
	if (!ft_strncmp(line, "EA ", 3))
		return (1);
	if (!ft_strncmp(line, "NO ", 3))
		return (2);
	if (!ft_strncmp(line, "SO ", 3))
		return (3);
	if (!ft_strncmp(line, "WE ", 3))
		return (4);
	if (!ft_strncmp(line, "F ", 2))
		return (5);
	if (!ft_strncmp(line, "C ", 2))
		return (6);
	return (0);
}

static void	init_map_and_player(char *map_path, t_game *game)
{
	if (check_elements(map_path, game) != 0b111111)
		clean_exit(2, "Map loading error.", game);
	map_elements_set(map_path, game);
	game->map.rows = count_line(map_path);
	game->map.layout = read_map(map_path, game);
	game->map.cols = get_max_cols(game->map.layout);
	init_player(game);
	fill_map(game->map.layout, game->map.cols, game);
	change_space_to_zero(&game->map);
	check_map(game);
	print_layout(game->map.layout);
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
