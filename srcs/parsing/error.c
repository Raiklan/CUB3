/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saich <saich@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 18:53:16 by saich             #+#    #+#             */
/*   Updated: 2022/07/21 14:54:37 by saich            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	*display_error(char *msg, int code, t_info *info)
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

static int	check_space_island(char **map, int i, int j, int limit)
{
	int ret;

	ret = 1;
	if (i == limit)
		return (0);
	if (map[i + 1] && map[i + 1][j] == ' ')
		ret = check_space_island(map, i + 1, j, limit);
	return (ret);
}

int	check_island(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		if (map[i][0] == '\n')
			return (1);
		while (map[i][j] && map[i][j] == ' ')
			j++;
		if (map[i][j] == '\0')
			return (1);
		i++;
	}
	while (map[0][j])
	{
		if (map[0][j] == ' ')
			if (!check_space_island(map, 0, j, map_length(map)))
				return (1);
		j++;
	}
	return (0);
}

static void	mlx_clear(t_info *info)
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
	{
		//mlx_clear_window(info->mlx.mlx_ptr, info->mlx.mlx_window);
		mlx_destroy_window(info->mlx.mlx_ptr, info->mlx.mlx_window);
	}
	if (info->mlx.win_ptr)
		mlx_destroy_window(info->mlx.mlx_ptr, info->mlx.win_ptr);
	if (info->mlx.mlx_ptr)
		mlx_destroy_display(info->mlx.mlx_ptr);
	free(info->mlx.mlx_ptr);
}

int	exit_window(t_info *info, char *msg)
{
	mlx_clear(info);
	display_error(msg, EXIT_SUCCESS, info);
	return (1);
}
