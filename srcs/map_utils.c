/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42tokyo.jp>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 17:04:34 by yxu               #+#    #+#             */
/*   Updated: 2024/11/12 21:34:43 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	print_map(char **map)
{
	int	x;

	if (map == NULL)
		return (0);
	x = 0;
	while (map[x])
	{
		printf("%s\n", map[x]);
		x++;
	}
	printf("\n");
	return (0);
}

int	free_map(char **map)
{
	int	x;

	if (map == NULL)
		return (0);
	x = 0;
	while (map[x])
	{
		free(map[x]);
		x++;
	}
	free(map);
	return (0);
}
