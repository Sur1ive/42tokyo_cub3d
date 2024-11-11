/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42tokyo.jp>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 18:01:27 by yxu               #+#    #+#             */
/*   Updated: 2024/11/12 00:08:00 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "key_linux.h"

int	key_handler(int key, t_data *data)
{
	if (key == K_ESC)
		clean_exit(MANUAL_QUIT, "Manual exit\n", data);
	if (key == K_W || key == K_A || key == K_S || key == K_D)
	{
	}
	return (0);
}
