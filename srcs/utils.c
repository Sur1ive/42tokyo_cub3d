/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakagawashinta <nakagawashinta@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 23:17:52 by yxu               #+#    #+#             */
/*   Updated: 2024/12/28 02:07:43 by nakagawashi      ###   ########.fr       */
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
	{
		free(line);
		line = get_next_line(fd);
	}
	while (line)
	{
		nb++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (nb);
}

int	is_number(const char *str)
{
	if (!str || *str == '\0')
		return (0);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
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

double	min(double x1, double x2)
{
	if (x1 > x2)
		return (x2);
	else
		return (x1);
}
