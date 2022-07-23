/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saich <saich@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 18:53:16 by saich             #+#    #+#             */
/*   Updated: 2022/07/23 15:32:15 by saich            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_space_island(char **map, int i, int j, int limit)
{
	int	ret;

	ret = 1;
	if (i == limit)
		return (0);
	if (map[i + 1] && map[i + 1][j] && map[i + 1][j] == ' ')
		ret = check_space_island(map, i + 1, j, limit);
	return (ret);
}

static int	check_line_space(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] == ' ')
	{
		i++;
	}
	if (!line[i])
		return (1);
	return (0);
}

int	check_island(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		if (check_line_space(map[i]))
			return (1);
		while (map[i][j])
		{
			if (map[i][j] == '\n')
				return (1);
			j++;
		}
		i++;
	}
	if (check_col(map))
		return (1);
	return (0);
}

void	mlx_clear(t_info *info)
{
	if (info->env.wall_ea.tex_ptr)
		mlx_destroy_image(info->mlx.mlx_ptr, info->env.wall_ea.tex_ptr);
	if (info->env.wall_no.tex_ptr)
		mlx_destroy_image(info->mlx.mlx_ptr, info->env.wall_no.tex_ptr);
	if (info->env.wall_so.tex_ptr)
		mlx_destroy_image(info->mlx.mlx_ptr, info->env.wall_so.tex_ptr);
	if (info->env.wall_we.tex_ptr)
		mlx_destroy_image(info->mlx.mlx_ptr, info->env.wall_we.tex_ptr);
	if (info->mlx.img_ptr)
		mlx_destroy_image(info->mlx.mlx_ptr, info->mlx.img_ptr);
	if (info->mlx.mlx_window)
		mlx_destroy_window(info->mlx.mlx_ptr, info->mlx.mlx_window);
	if (info->mlx.win_ptr)
		mlx_destroy_window(info->mlx.mlx_ptr, info->mlx.win_ptr);
	if (info->mlx.mlx_ptr)
		mlx_destroy_display(info->mlx.mlx_ptr);
	free(info->mlx.mlx_ptr);
}

int	suppr_empty_line_map(char **map, int i, int j, int tmp)
{
	while (i >= 0)
	{
		j = ft_strlen(map[i]);
		while (j >= 0)
		{
			if (map[i][j] == '1')
			{
				tmp = i;
				i++;
				while (map[i])
				{
					free(map[i]);
					i++;
				}
				map[tmp + 1] = NULL;
				return (0);
			}
			j--;
		}
		i--;
	}
	return (0);
}
