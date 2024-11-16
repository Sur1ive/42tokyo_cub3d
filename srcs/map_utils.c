/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42tokyo.jp>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 17:04:34 by yxu               #+#    #+#             */
/*   Updated: 2024/11/16 19:31:25 by yxu              ###   ########.fr       */
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
