/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anakagaw <anakagaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 17:04:34 by yxu               #+#    #+#             */
/*   Updated: 2025/01/01 17:23:02 by anakagaw         ###   ########.fr       */
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

// void	print_layout(char **layout)
// {
// 	int	x;

// 	if (layout == NULL)
// 		return ;
// 	x = 0;
// 	while (layout[x])
// 	{
// 		printf("%s\n", layout[x]);
// 		x++;
// 	}
// 	printf("\n");
// }

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

int	load_texture(t_game *game, char *filepath, unsigned char id)
{
	t_element	*element;

	element = (t_element *)malloc(sizeof(t_element));
	if (element == NULL)
		return (0);
	element->texture.img = mlx_xpm_file_to_image(game->mlx,
			filepath, &element->texture.width, &element->texture.height);
	if (element->texture.img == NULL)
	{
		free(element);
		return (0);
	}
	element->texture.addr = mlx_get_data_addr(element->texture.img,
			&element->texture.bits_per_pixel, &element->texture.line_length,
			&element->texture.endian);
	element->id = id;
	element->next = game->map.elements;
	game->map.elements = element;
	return (1);
}

void	change_space_to_zero(t_map *map)
{
	int		i;
	int		j;

	i = 0;
	while (map->layout[i])
	{
		j = 0;
		while (map->layout[i][j])
		{
			if (map->layout[i][j] == ' ')
				map->layout[i][j] = '0';
			j++;
		}
		i++;
	}
}
