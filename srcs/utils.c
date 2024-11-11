/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42tokyo.jp>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 23:17:52 by yxu               #+#    #+#             */
/*   Updated: 2024/11/12 00:28:35 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_game(t_data *data)
{
	(void)data;
}

void	clean_exit(int exitcode, char *errmsg, t_data *data)
{
	free_game(data);
	if (exitcode == MANUAL_QUIT)
	{
		printf("Manual quit\n");
		exit(EXIT_SUCCESS);
	}
	else
	{
		ft_dprintf(STDERR_FILENO, "Error\n%s\n", errmsg);
		exit(EXIT_FAILURE);
	}
}
