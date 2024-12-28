/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 17:12:33 by yxu               #+#    #+#             */
/*   Updated: 2024/12/28 11:51:30 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	count_words(char *str, char c)
{
	int	num_of_words;
	int	i;

	if (str == NULL)
		return (0);
	i = 0;
	num_of_words = 1;
	while (str[i] != '\0')
	{
		if (str[i] == c && str[i])
			num_of_words += 1;
		i++;
	}
	return (num_of_words);
}

static void	ft_split_sub(char **splited, char *str, char c)
{
	int		head;
	int		tail;
	int		j;

	tail = 0;
	head = 0;
	j = 0;
	while (str[tail] != '\0')
	{
		if (str[tail] == c)
		{
			splited[j++] = ft_substr(str, head, tail - head);
			head = tail + 1;
		}
		tail++;
	}
	splited[j++] = ft_substr(str, head, tail - head);
	splited[j] = NULL;
}

static void	freepp(char **pp, int i)
{
	int	j;

	j = 0;
	while (j < i)
		free(pp[j++]);
	free(pp);
}

char	**rgb_split(char const *s, char c)
{
	char	**splited;
	int		num_of_words;
	int		i;

	if (s == NULL)
		return (NULL);
	num_of_words = count_words((char *)s, c);
	splited = (char **)malloc((num_of_words + 1) * sizeof(char *));
	if (splited == NULL)
		return (NULL);
	ft_split_sub(splited, (char *)s, c);
	i = 0;
	while (i < num_of_words)
	{
		if (splited[i] == NULL)
		{
			freepp(splited, i);
			return (NULL);
		}
		i++;
	}
	return (splited);
}
