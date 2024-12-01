/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42tokyo.jp>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 12:01:40 by yxu               #+#    #+#             */
/*   Updated: 2024/12/01 13:53:45 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_ext(char *path)
{
	char	*file_ext;

	file_ext = ".cub";
	if (ft_strlen(path) < 5
		|| ft_strncmp(&path[ft_strlen(path) - 4], file_ext, 4))
		return (-1);
	return (0);
}

void	argv_checker(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("Invalid arguments number\n");
		exit(EXIT_FAILURE);
	}
	if (check_ext(argv[1]))
	{
		printf("Invalid file extension, use .cub\n");
		exit(EXIT_FAILURE);
	}
}

