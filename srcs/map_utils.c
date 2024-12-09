/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42tokyo.jp>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 17:04:34 by yxu               #+#    #+#             */
/*   Updated: 2024/12/10 22:45:32 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_image	*get_texture_with_id(t_game *game, unsigned char id)
{
	t_element	*elements;

	elements = game->map.elements;
	while (elements)
	{
		if (elements->id == id)
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

void	load_texture(t_game *game, char *filepath, unsigned char id)
{
	t_element	*element;

	element = (t_element *)malloc(sizeof(t_element));
	if (element == NULL)
		clean_exit(INIT_ERR, "malloc error", game);
	element->texture.img = mlx_xpm_file_to_image(game->mlx,
			filepath, &element->texture.width, &element->texture.height);
	if (element->texture.img == NULL)
		clean_exit(INIT_ERR, "error when loading textures", game);
	element->texture.addr = mlx_get_data_addr(element->texture.img,
			&element->texture.bits_per_pixel, &element->texture.line_length,
			&element->texture.endian);
	element->id = id;
	element->next = game->map.elements;
	game->map.elements = element;
}

void	mock_map_maker(t_game *game)
{
	game->map.layout = (char **)malloc(5 * sizeof(char *));
	game->map.layout[4] = NULL;
	game->map.layout[0] = ft_strdup("11111111");
	game->map.layout[1] = ft_strdup("1N000001");
	game->map.layout[2] = ft_strdup("10010011");
	game->map.layout[3] = ft_strdup("11111111");
	game->map.rows = 4;
	game->map.cols = 8;
	load_texture(game, "textures/Textures-1.xpm", EID_WALL_N);
	load_texture(game, "textures/Textures-2.xpm", EID_WALL_S);
	load_texture(game, "textures/Textures-3.xpm", EID_WALL_W);
	load_texture(game, "textures/Textures-4.xpm", EID_WALL_E);
	game->map.ceiling_color = create_trgb(0, 102, 170, 255);
	game->map.floor_color = create_trgb(0, 99, 62, 0);
	game->player.direction = 0;
	game->player.location.x = 1.5;
	game->player.location.y = 1.5;
}
