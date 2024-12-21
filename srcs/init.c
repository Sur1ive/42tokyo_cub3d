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

static void	game_preset(t_game *game)
{
	game->mlx = NULL;
	game->win = NULL;
	game->map.layout = NULL;
	game->map.elements = NULL;
	game->map.floor_color = 0;
	game->map.ceiling_color = 0;
}

int	is_number(const char *str)
{
	if (!str || *str == '\0')
		return (0);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

static int	get_floor_ceiling_colors(char *type, char *color, t_game *game)
{
	char	**rgb;
	int		n_rgb[3];
	int		i;

	rgb = ft_split(color, ',');
	if (!rgb)
		return (0);
	i = 0;
	while (rgb[i])
	{
		if (!is_number(rgb[i]))
			return (0);
		i++;
	}
	if (i != 3)
		return (0);
	i--;
	while (i >= 0)
	{
		n_rgb[i] = ft_atoi(rgb[i]);
		if (n_rgb[i] < 0 || n_rgb[i] > 255)
			return (0);
		i--;
	}
	free2(rgb);
	if (!ft_strcmp(type, "F"))
		game->map.floor_color = create_trgb(0, n_rgb[0], n_rgb[1], n_rgb[2]);
	else
		game->map.ceiling_color = create_trgb(0, n_rgb[0], n_rgb[1], n_rgb[2]);
	return (1);
}

static int	handle_element(char **split, t_game *game)
{
	int i;

	i = 0;
	while (split[i])
		i++;
	if (i != 2)
		return (0);
	if (ft_strchr("NSEW", split[0][0]))
		load_texture(game, split[1], split[0][0]);
	else
	{
		if (!get_floor_ceiling_colors(split[0], split[1], game))
			return (0);
	}
	return (1);
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
			if (!handle_element(split, game))
			{
				free2(split);
				free(line);
				close(fd);
				clean_exit(2, "Invalid element\n" , game);
			}
			free2(split);
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

void	check_elements(char *map_path, t_game *game)
{
	int		fd, i;
	const char	*elements[6] = {""};
	char	*line;

	fd = open(map_path, O_RDONLY);
	if (fd == -1)
		clean_exit(2, "Map loading error\n", game);
	line = get_next_line(fd);
	i = 0;
	while (line && i < 6)
	{
		if (*line != '\n' && *line != '\0')
		{
			if (ft_strncmp(elements[i], line, ft_strlen(elements[i])))
			{
				free(line);
				close(fd);
				clean_exit(2, "Missing or invalid element", game);
			}
			i++;
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (i < 6)
		clean_exit(2, "Missing elements in map file", game);
}


static void	init_map_and_player(char *map_path, t_game *game)
{
	check_elements(map_path, game);
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
