/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42tokyo.jp>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 12:16:45 by nakagawashi       #+#    #+#             */
/*   Updated: 2024/12/24 23:25:00 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static double	get_player_dir(char direction)
{
	if (direction == 'N')
		return (PI * 3 / 2);
	else if (direction == 'S')
		return (PI * 1 / 2);
	else if (direction == 'E')
		return (0);
	else if (direction == 'W')
		return (PI);
	return (-1);
}

void	init_player(t_game *game)
{
	int		i;
	int		j;

	j = 0;
	while (game->map.layout[j])
	{
		i = 0;
		while (game->map.layout[j][i])
		{
			if (ft_strchr("NSEW", game->map.layout[j][i]))
			{
				game->player.location.x = i + 0.5;
				game->player.location.y = j + 0.5;
				game->player.direction = get_player_dir(game->map.layout[j][i]);
				return ;
			}
			i++;
		}
		j++;
	}
}
