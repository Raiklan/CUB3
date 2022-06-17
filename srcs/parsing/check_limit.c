/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_limit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saich <saich@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 17:36:00 by saich             #+#    #+#             */
/*   Updated: 2022/06/17 18:24:18 by saich            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static	int	check_limit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '1' || str[i] == ' ')
			i++;
		else
			return (0);
	}
	return (1);
}

static int	check_last_line(char **map, int i)
{
	int	j;

	j = -1;
	while (map[i][++j] == ' ')
		;
	while (map[i][++j])
	{
		if (map[i][j] == ' ')
			if (!check_closed(map, i, j, 0))
				return (0);
	}
	return (1);
}

static int	check_diff(char *current_line, char *past_line, int diff)
{
	char	*line_long;
	char	*line_short;
	int		i;

	if (diff > 0)
	{
		line_long = current_line;
		line_short = past_line;
	}
	else
	{
		line_long = past_line;
		line_short = current_line;
	}
	i = ft_strlen(line_short) - 1;
	while (line_long[++i])
		if (line_long[i] != '1')
			return (0);
	return (1);
}

static void	get_pos(char **map, t_info *info)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E'
				|| map[i][j] == 'W')
			{
				if (info->env.pos_dir == 0)
				{
					info->env.pos_dir = map[i][j];
					info->env.pos_coor[0] = i;
					info->env.pos_coor[1] = j;
				}
				else if (info->env.pos_dir != 0)
					display_error("position already set", EXIT_FAILURE, info);
			}
			j++;
		}
		i++;
	}
}

static int	check_map_outline(char **map)
{
	int	i;
	int	j;
	int	diff;

	i = 0;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j] == ' ')
			;
		if (map[i][j] != '1')
			return (10);
		diff = ft_strlen(map[i]) - ft_strlen(map[i - 1]);
		if (!check_diff(map[i], map[i - 1], diff))
			return (11);
		if (check_last_wall(map[i], 0))
			return (11);
		if (!check_space(map, i, j))
			return (12);
	}
	if (!check_last_line(map, --i))
		return (13);
	return (1);
}

void	parse_map(char **map, t_info *info)
{
	int	ret;

	if (!check_limit(map[0]) || !check_limit(map[map_length(map)]))
		display_error("Error map", 10, info);
	get_pos(map, info);
	if (info->env.pos_dir == 0)
		display_error("no starting position defined", EXIT_FAILURE, info);
	ret = check_map_outline(map);
	handle_error(ret, info);
}

void	display_error(char *msg, int code, t_info *info)
{
	if (code != 0)
		printf("Error\n");
	printf("%s\n", msg);
	free_info(info);
	exit(code);
}

void	handle_error(int ret, t_info *info)
{
	if (ret == 10)
		display_error("missing 1 on top of a line", EXIT_FAILURE, info);
	else if (ret == 11)
		display_error("map is not surrounded by 1", EXIT_FAILURE, info);
	else if (ret == 12)
		display_error("space is not surrounded by 1", EXIT_FAILURE, info);
	else if (ret == 13)
		display_error("missing 1 at the end of a line", EXIT_FAILURE, info);
}
