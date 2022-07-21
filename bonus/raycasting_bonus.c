/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saich <saich@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 15:17:50 by saich             #+#    #+#             */
/*   Updated: 2022/07/20 18:17:04 by saich            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	init_raycast(t_info *info, int x)
{
	info->cast.hit = 0;
	info->cast.mapx = (int)info->cast.posx;
	info->cast.mapy = (int)info->cast.posy;
	info->cast.camerax = 2 * x / (float)info->resolution.x - 1;
	info->cast.ray_dirx = info->cast.dirx + info->cast.planx
		* info->cast.camerax;
	info->cast.ray_diry = info->cast.diry + info->cast.plany
		* info->cast.camerax;
	info->cast.delta_distx = fabs(1 / info->cast.ray_dirx);
	info->cast.delta_disty = fabs(1 / info->cast.ray_diry);
}

void	build_ray(t_info *info)
{
	if (info->cast.ray_dirx < 0)
	{
		info->cast.stepx = -1;
		info->cast.side_distx = (info->cast.posx - info->cast.mapx)
			* info->cast.delta_distx;
	}
	else
	{
		info->cast.stepx = 1;
		info->cast.side_distx = (info->cast.mapx + 1.0 - info->cast.posx)
			* info->cast.delta_distx;
	}
	if (info->cast.ray_diry < 0)
	{
		info->cast.stepy = -1;
		info->cast.side_disty = (info->cast.posy - info->cast.mapy)
			* info->cast.delta_disty;
	}
	else
	{
		info->cast.stepy = 1;
		info->cast.side_disty = (info->cast.mapy + 1 - info->cast.posy)
			* info->cast.delta_disty;
	}
}

void	build_wall(t_info *info)
{
	if (info->cast.side == 0)
		info->cast.perpwalldist = (info->cast.mapx - info->cast.posx
				+ (1 - info->cast.stepx) / 2) / info->cast.ray_dirx;
	else
		info->cast.perpwalldist = (info->cast.mapy - info->cast.posy
				+ (1 - info->cast.stepy) / 2) / info->cast.ray_diry;
	info->cast.line_height = (int)(info->resolution.y
			/ info->cast.perpwalldist);
	info->cast.draw_start = -(info->cast.line_height)
		/ 2 + info->resolution.y / 2;
	if (info->cast.draw_start < 0)
		info->cast.draw_start = 0;
	info->cast.draw_end = info->cast.line_height
		/ 2 + info->resolution.y / 2;
	if (info->cast.draw_end >= info->resolution.y)
		info->cast.draw_end = info->resolution.y;
}

void	find_wall(t_info	*info)
{
	while (info->cast.hit == 0)
	{
		if (info->cast.side_distx < info->cast.side_disty)
		{
			info->cast.side_distx += info->cast.delta_distx;
			info->cast.mapx += info->cast.stepx;
			info->cast.side = 0;
		}
		else
		{
			info->cast.side_disty += info->cast.delta_disty;
			info->cast.mapy += info->cast.stepy;
			info->cast.side = 1;
		}
		if (info->map[info->cast.mapx][info->cast.mapy] == '1')
			info->cast.hit = 1;
	}
}

int	raycasting(t_info *info)
{
	int	x;

	x = -1;
	ft_move(info);
	while (++x < info->resolution.x)
	{
		init_raycast(info, x);
		build_ray(info);
		find_wall(info);
		build_wall(info);
		draw_background(info, x);
		draw_wall(info, x);
	}
	draw_minimap(info, minimap_init());
	mlx_put_image_to_window(info->mlx.mlx_ptr, info->mlx.win_ptr,
		info->mlx.img_ptr, 0, 0);
	return (0);
}
