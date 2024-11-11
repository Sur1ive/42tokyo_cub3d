/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42tokyo.jp>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 22:22:15 by yxu               #+#    #+#             */
/*   Updated: 2024/11/12 00:27:11 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_ext(char *path)
{
	char	*file_ext;

	file_ext = ".cub";
	if (ft_strlen(path) < 5
		|| ft_strncmp(&path[ft_strlen(path) - 4], file_ext, 4))
		return (-1);
	return (0);
}

void	argv_parser(int argc, char **argv)
{
	if (argc != 2)
		clean_exit(ERR, "Invalid arguments number", NULL);
	if (check_ext(argv[1]))
		clean_exit(ERR, "Invalid file extension, use .cub", NULL);
}

int	destory_win(t_data *data)
{
	clean_exit(MANUAL_QUIT, "Manual exit\n", data);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	argv_parser(argc, argv);
	init_game(argv[1], &data);
	mlx_key_hook(data.win, key_handler, &data);
	mlx_hook(data.win, 17, (1L << 0), destory_win, &data);
	mlx_loop(data.mlx);
}
