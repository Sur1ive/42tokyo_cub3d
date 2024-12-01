/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42tokyo.jp>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 17:04:34 by yxu               #+#    #+#             */
/*   Updated: 2024/12/01 13:30:34 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_image	*get_texture_with_id(t_element *elements, unsigned char id[2])
{
	while (elements)
	{
		if (elements->id[0] == id[0] && elements->id[1] == id[1])
			return (&elements->texture);
		elements = elements->next;
	}
	return (NULL);
}

void	print_layout(char **layout)
{
	int	x;

	if (layout == NULL)
		return ;
	x = 0;
	while (layout[x])
	{
		printf("%s\n", layout[x]);
		x++;
	}
	printf("\n");
}

void	free_map(t_game *game)
{
	t_element	*element;
	t_element	*next;

	element = game->map.elements;
	while (element)
	{
		if (element->texture.img)
			mlx_destroy_image(game->mlx, element->texture.img);
		next = element->next;
		free(element);
		element = next;
	}
	free2(game->map.layout);
}

void	read_texture(t_game *game, char *filepath, unsigned char id[2])
{
	t_element	*element;

	element = (t_element *)malloc(sizeof(t_element));
	if (element == NULL)
		clean_exit(INIT_ERR, "malloc error", game);
	element->texture.img = mlx_xpm_file_to_image(game->mlx,
			filepath, &element->texture.width, &element->texture.height);
	if (element->texture.img == NULL)
		clean_exit(INIT_ERR, "error while reading textures", game);
	element->id[0] = id[0];
	element->id[1] = id[1];
	element->next = game->map.elements;
	game->map.elements = element;
}

void	mock_map_maker(t_game *game)
{
	game->map.layout = (char **)malloc(4 * sizeof(char *));
	game->map.layout[3] = NULL;
	game->map.layout[0] = ft_strdup("111");
	game->map.layout[1] = ft_strdup("1N1");
	game->map.layout[2] = ft_strdup("111");
	game->map.rows = 3;
	game->map.cols = 3;
	read_texture(game, "textures/Textures-1.xpm", (unsigned char[])EID_WALL_N);
	read_texture(game, "textures/Textures-2.xpm", (unsigned char[])EID_WALL_S);
	read_texture(game, "textures/Textures-3.xpm", (unsigned char[])EID_WALL_W);
	read_texture(game, "textures/Textures-4.xpm", (unsigned char[])EID_WALL_E);
	read_texture(game, "textures/Textures-5.xpm", (unsigned char[])EID_CEILING);
	read_texture(game, "textures/Textures-6.xpm", (unsigned char[])EID_FLOOR);
}
