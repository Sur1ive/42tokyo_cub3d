/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakagawashinta <nakagawashinta@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 23:17:52 by yxu               #+#    #+#             */
/*   Updated: 2024/12/04 00:13:06 by nakagawashi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// free char **
void	free2(char **p)
{
	int	i;

	if (p == NULL)
		return ;
	i = 0;
	while (p[i])
		free(p[i++]);
	free(p);
}

int	count_line(char *path)
{
	int		fd;
	int		nb;
	char	*line;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (-1);
	nb = 0;
	line = get_next_line(fd);
	while (is_element(line) || line[0] == '\n')
		line = get_next_line(fd);
	while (line)
	{
		nb++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (nb);
}

int	is_element(char	*line)
{
	if (!ft_strncmp(line, EID_WALL_E, 2) || !ft_strncmp(line, EID_WALL_N, 2)
		|| !ft_strncmp(line, EID_WALL_S, 2) || !ft_strncmp(line, EID_WALL_W, 2))
		return (1);
	if (*line == 'F' || *line == 'C')
		return (1);
	return (1);
}

double	limit_angle(double angle)
{
	if (angle < 0)
		angle += 2 * PI;
	else if (angle > 2 * PI)
		angle -= 2 * PI;
	return (angle);
}
