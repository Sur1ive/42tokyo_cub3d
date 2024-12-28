/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_elements.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakagawashinta <nakagawashinta@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 02:03:23 by nakagawashi       #+#    #+#             */
/*   Updated: 2024/12/28 02:12:12 by nakagawashi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	handle_error(char *line, char **split, int fd, t_game *game)
{
	if (line)
		free(line);
	if (split)
		free2(split);
	if (fd != -1)
		close(fd);
	clean_exit(2, "Map loading error.\n", game);
}

static int	get_floor_ceiling_colors(char *color, int n_rgb[3])
{
	char	**rgb;
	int		i;
	int		val;
	bool	flag;

	flag = false;
	rgb = ft_split(color, ',');
	if (!rgb)
		return (0);
	i = 0;
	while (rgb[i] && flag == false)
	{
		if (!is_number(rgb[i]))
			flag = true;
		val = ft_atoi(rgb[i]);
		if (val < 0 || val > 255)
			flag = true;
		n_rgb[i] = val;
		i++;
	}
	free2(rgb);
	if (flag || i != 3)
		return (0);
	return (1);
}

static int	load_element(char **split, t_game *game)
{
	int	n_rgb[3];
	int	*f_color;
	int	*c_color;

	f_color = &game->map.floor_color;
	c_color = &game->map.ceiling_color;
	if (!split || !split[0] || !split[1] || split[2])
		return (0);
	if (ft_strchr("NSEW", split[0][0]))
		load_texture(game, split[1], split[0][0]);
	else
	{
		if (!get_floor_ceiling_colors(split[1], n_rgb))
			return (0);
		if (!ft_strcmp(split[0], "F"))
			*f_color = create_trgb(0, n_rgb[0], n_rgb[1], n_rgb[2]);
		else
			*c_color = create_trgb(0, n_rgb[0], n_rgb[1], n_rgb[2]);
	}
	return (1);
}

void	map_elements_set(char *path, t_game *game)
{
	int		fd;
	char	*line;
	char	**split;

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
			if (!load_element(split, game))
				handle_error(line, split, fd, game);
			free2(split);
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

int	check_elements(char *map_path, t_game *game)
{
	int		fd;
	int		found_flags;
	char	*line;
	int		element_id;

	fd = open(map_path, O_RDONLY);
	if (fd == -1)
		clean_exit(2, "Map loading error\n", game);
	found_flags = 0;
	line = get_next_line(fd);
	while (line && found_flags != 0b111111)
	{
		element_id = is_element(line);
		if (element_id > 0)
		{
			if (found_flags & (1 << (element_id - 1)))
				handle_error(line, NULL, fd, game);
			found_flags |= (1 << (element_id - 1));
		}
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return(found_flags);
}
