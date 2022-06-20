/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_space.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saich <saich@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 19:19:30 by saich             #+#    #+#             */
/*   Updated: 2022/06/20 19:31:55 by saich            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_closed_first(char **map, int i, int j)
{
	int	ret;

	ret = 0;
	if (map[i][j + 1] == '1' || map[i][j + 1] == ' ')
		ret++;
	if (map[i + 1][j] == '1' || map[i + 1][j] == ' ')
		ret++;
	if (map[i][j - 1] == '1' || map[i][j - 1] == ' ')
		ret++;
	if (ret == 3)
		return (1);
	return (0);
}

static int	check_space_first(char **map)
{
	int	i;

	i = 0;
	while (map[0][i] == ' ')
			i++;
	while (map[0][i])
	{
		if (map[0][i] == ' ')
		{
			if (!check_closed_first(map, 0, i))
				return (0);
		}
		i++;
	}
	return (1);
}

int	check_closed(char **map, int i, int j, int last)
{
	int	ret;

	ret = 0;
	if (map[i][j + 1] == '1' || map[i][j + 1] == ' ')
		ret++;
	if (last)
		if (map[i + 1][j] == '1' || map[i + 1][j] == ' ')
			ret++;
	if (map[i][j - 1] == '1' || map[i][j - 1] == ' ')
		ret++;
	if (map[i - 1][j] == '1' || map[i - 1][j] == ' ')
		ret++;
	if (last && ret == 4)
		return (1);
	else if (!last && ret == 3)
		return (1);
	return (0);
}

int	check_space_closed(char **map, int i, int j, int limit)
{
	int	ret;

	ret = 1;
	if (i == limit)
		return (2);
	if (map[i][j + 1] == ' ')
		ret = check_space_closed(map, i, j + 1, limit);
	else if (map[i + 1][j] == ' ')
		ret = check_space_closed(map, i + 1, j, limit);
	else if (map[i + 1][j + 1] == ' ')
		ret = check_space_closed(map, i + 1, j + 1, limit);
	if (!check_closed(map, i, j, 1))
		return (0);
	return (ret);
}

int	check_space(char **map, int i, int j)
{
	while (map[i][++j])
	{
		if (i == 1 && !check_space_first(map))
			return (0);
		if (map[i][j] != '1' && map[i][j] != '0' && map[i][j] != 'N' && \
map[i][j] != 'S' && map[i][j] != 'W' && map[i][j] != 'E' && map[i][j] != ' ')
			return (print_error("Character of the map \
can only be : 1, 0, N, E, S, W or spaces\n"));
		if (map[i][j] == ' ')
		{
			if (check_space_closed(map, i, j, map_length(map)) == 0)
				return (0);
		}
	}
	return (1);
}
