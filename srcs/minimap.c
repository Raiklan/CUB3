/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleroy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 13:29:39 by aleroy            #+#    #+#             */
/*   Updated: 2022/07/21 13:29:48 by aleroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_player_rays(t_info *info, t_minimap *minimap)
{
	t_coor	coor;
	int		x;

	x = -1;
	while (++x < info->resolution.x)
	{
		info->minimap_color = 0x0000ff;
		coor.x1 = info->cast.posy * minimap->tile_size;
		coor.y1 = info->cast.posx * minimap->tile_size;
		init_raycast(info, x);
		build_ray(info);
		find_wall(info);
		if (info->cast.side == 0)
			info->minimap_color /= 2;
		coor.xold = info->cast.mapy * minimap->tile_size;
		coor.yold = info->cast.mapx * minimap->tile_size;
		bresenham_new(info, &coor);
	}
	draw_player(info, minimap);
}

void	draw_player(t_info *info, t_minimap *minimap)
{
	t_coor	coor;

	info->minimap_color = 0xff0000;
	coor.x1 = info->cast.posy * minimap->tile_size + info->cast.diry * 10;
	coor.y1 = info->cast.posx * minimap->tile_size + info->cast.dirx * 10;
	coor.xold = info->cast.posy * minimap->tile_size;
	coor.yold = info->cast.posx * minimap->tile_size;
	bresenham_new(info, &coor);
	coor.x1 = info->cast.posy * minimap->tile_size - info->cast.dirx * 10;
	coor.y1 = info->cast.posx * minimap->tile_size + info->cast.diry * 10;
	coor.xold = info->cast.posy * minimap->tile_size;
	coor.yold = info->cast.posx * minimap->tile_size;
	bresenham_new(info, &coor);
	coor.x1 = info->cast.posy * minimap->tile_size + info->cast.dirx * 10;
	coor.y1 = info->cast.posx * minimap->tile_size - info->cast.diry * 10;
	coor.xold = info->cast.posy * minimap->tile_size;
	coor.yold = info->cast.posx * minimap->tile_size;
	bresenham_new(info, &coor);
}

t_minimap	minimap_init(void)
{
	t_minimap	tmp;

	tmp.x = 0;
	tmp.y = 0;
	tmp.i = 0;
	tmp.tile_size = 10;
	return (tmp);
}

void	chose_minimap_color(t_info *info, t_minimap *minimap)
{
	if (minimap->pixel_count == 0 || minimap->col_count == 0)
		info->minimap_color = 0x0;
	else if (minimap->pixel_count + 1 == minimap->tile_size
		|| minimap->col_count + 1 == minimap->tile_size)
		info->minimap_color = 0xffffff;
	else if (info->map[minimap->i][minimap->j] == '0' ||
				info->map[minimap->i][minimap->j] == 'N' ||
				info->map[minimap->i][minimap->j] == 'S' ||
				info->map[minimap->i][minimap->j] == 'E' ||
				info->map[minimap->i][minimap->j] == 'W')
		info->minimap_color = 0xbdb76b;
	else if (info->map[minimap->i][minimap->j] == '\t' ||
				info->map[minimap->i][minimap->j] == ' ')
		info->minimap_color = 0xcccccc;
	else
		info->minimap_color = 0x696969;
}

void	draw_minimap(t_info *info, t_minimap minimap)
{
	while (info->map[minimap.i])
	{
		minimap.col_count = 0;
		while (minimap.col_count < minimap.tile_size)
		{
			minimap.j = 0;
			while (info->map[minimap.i][minimap.j])
			{
				minimap.pixel_count = 0;
				while (minimap.pixel_count < minimap.tile_size)
				{
					chose_minimap_color(info, &minimap);
					img_pix_put(info, minimap.x, minimap.y);
					minimap.pixel_count++;
					minimap.x++;
				}
				minimap.j++;
			}
			minimap.y++;
			minimap.col_count++;
			minimap.x = 0;
		}
		minimap.i++;
	}
	draw_player(info, &minimap);
}
