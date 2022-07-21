/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saich <saich@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 16:27:39 by saich             #+#    #+#             */
/*   Updated: 2022/07/21 16:52:04 by saich            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_wall_hit(t_info *info)
{
	if (info->cast.side == 0)
		info->cast.wall_hit = info->cast.posy
			+ info->cast.perpwalldist * info->cast.ray_diry;
	else
		info->cast.wall_hit = (info->cast.perpwalldist * info->cast.ray_dirx)
			+ info->cast.posx;
	info->cast.wall_hit -= floor(info->cast.wall_hit);
}

void	build_t(t_info *info, t_texture *tex, int i)
{
	int				texy;
	int				texx;
	unsigned int	color;

	set_wall_hit(info);
	texx = ((int)(info->cast.wall_hit * (float)tex->w));
	texx = tex->w - texx - 1;
	while (info->cast.draw_start < info->cast.draw_end)
	{
		texy = (info->cast.draw_start * 2 - info->resolution.y
				+ info->cast.line_height) * (tex->h / 2)
			/ info->cast.line_height;
		color = tex->tex_addr[(tex->w * texy) + texx];
		info->mlx.img_addr[info->cast.draw_start
			* info->resolution.x + i] = color;
		info->cast.draw_start++;
	}
}

void	draw_wall(t_info *info, int x)
{
	if (!info->cast.side && info->cast.ray_dirx < 0)
		build_t(info, &info->env.wall_no, x);
	else if (!info->cast.side && info->cast.ray_dirx > 0)
		build_t(info, &info->env.wall_so, x);
	else if (info->cast.side && info->cast.ray_diry > 0)
		build_t(info, &info->env.wall_we, x);
	else if (info->cast.side && info->cast.ray_diry < 0)
		build_t(info, &info->env.wall_ea, x);
}

void	draw_background(t_info *info, int i)
{
	int	j;

	j = 0;
	while (j < info->cast.draw_start)
	{
		info->mlx.img_addr[j * info->resolution.x + i]
			= info->env.color_ceil;
		j++;
	}
	j = info->cast.draw_end;
	while (j < info->resolution.y)
	{
		info->mlx.img_addr[j * info->resolution.x + i]
			= info->env.color_floor;
		j++;
	}
}
