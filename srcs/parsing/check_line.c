/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saich <saich@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 14:43:36 by saich             #+#    #+#             */
/*   Updated: 2022/07/23 15:27:06 by saich            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	last_wall_line(char *line)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (line[i])
	{
		if (line[i] == '1')
			ret = i;
		i++;
	}
	return (ret);
}

int	check_col(char **map)
{
	int	i;
	int	limit;

	i = 0;
	limit = check_last_col(map);
	while (map[0][i] && map[0][i] == ' ')
		i++;
	while (map[0][i])
	{
		if (map[0][i] == ' ' && i < limit)
		{
			if (!check_space_island(map, 0, i, map_length(map)))
				return (1);
		}
		i++;
	}
	return (0);
}

int	check_space_line(char **map, int i)
{
	int	j;

	j = 0;
	while (map[i][j])
	{
		if (j > last_wall_line(map[i]) && map[i][j] != ' ')
			return (1);
		j++;
	}
	return (0);
}
