/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleroy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 19:09:09 by aleroy            #+#    #+#             */
/*   Updated: 2022/01/04 19:09:12 by aleroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_rays_stuff(t_info *info, t_raycast *raycast)
{
	if (raycast->rangle < 0)
		raycast->rangle += 2 * PI;
	if (raycast->rangle > 2 * PI)
		raycast->rangle -= 2 * PI;
	raycast->rayx = info->player.x;
	raycast->rayy = info->player.y;
	raycast->ray_dirx = cos(raycast->rangle) * 5 ;
	raycast->ray_diry = sin(raycast->rangle) * 5;
	raycast->wall_hit = 0;
	if (raycast->ray_dirx == 0)
		raycast->next_full_x = 1e30;
	else
		raycast->next_full_x = sqrt(1 + (raycast->ray_diry * raycast->ray_diry) /
			(raycast->ray_dirx * raycast->ray_dirx));
	if (raycast->ray_diry == 0)
		raycast->next_full_y = 1e30;
	else
		raycast->next_full_y = sqrt(1 + (raycast->ray_dirx * raycast->ray_dirx) /
			(raycast->ray_diry * raycast->ray_diry));
}

void	get_rays_step_dir(t_info *info, t_raycast *raycast)
{
	if (raycast->ray_dirx < 0)
	{
		raycast->stepx = -1;
		raycast->le_restex = (info->player.x - raycast->rayx) *
		raycast->next_full_x;
	}
	else
	{
		raycast->stepx = 1;
		raycast->le_restex = (raycast->rayx + 1.0 - info->player.x) *
		raycast->next_full_x;
	}
	if (raycast->ray_diry < 0)
	{
		raycast->stepy = -1;
		raycast->le_restey = (info->player.y - raycast->rayy) *
		raycast->next_full_y;
	}
	else
	{
		raycast->stepy = 1;
		raycast->le_restey = (raycast->rayy + 1.0 - info->player.y) *
		raycast->next_full_y;
	}
}

void	get_wall_contact(t_info *info, t_raycast *raycast)
{
	while (raycast->wall_hit == 0)
	{
		if (raycast->le_restex < raycast->le_restey)
		{
			raycast->le_restex += raycast->next_full_x;
			raycast->rayx += raycast->stepx;
			raycast->side = 0;//x side
		}
		else
		{
			raycast->le_restey += raycast->next_full_y;
			raycast->rayy += raycast->stepy;
			raycast->side = 1;// y side
		}
		if (info->line[raycast->rayy / info->tile_size][raycast->rayx /
			info->tile_size] == '1')
			raycast->wall_hit = 1;
	}
}

void	get_wall_heigth(t_info *info, t_raycast *raycast)
{
	if(raycast->side == 0)
		raycast->perpWallDist = (raycast->le_restex - raycast->next_full_x) /
			2;//can change the ratio (/ x) if tile_size is changed
	else
		raycast->perpWallDist = (raycast->le_restey - raycast->next_full_y) /
			2;
	if (raycast->perpWallDist <= 0)
		raycast->perpWallDist = 0.1;
	else
		raycast->perpWallDist = raycast->perpWallDist *
			cos(raycast->rangle - info->player.angle);
	raycast->lineHeight = (int)(info->wd_height / raycast->perpWallDist);
	raycast->drawStart = -raycast->lineHeight / 2 + info->wd_height / 2;
	if (raycast->drawStart < 0)
		raycast->drawStart = 0;
	raycast->drawEnd = raycast->lineHeight / 2 + info->wd_height / 2;
	if(raycast->drawEnd >= info->wd_height)
		raycast->drawEnd = info->wd_height - 1;
}

int    render(t_info *info)
{
    t_img    tmp;

    tmp.img_ptr = mlx_new_image(info->id, info->wd_width, info->wd_height);
    if (tmp.img_ptr == NULL)
        return (destroyer(info, info->line));
    tmp.addr = mlx_get_data_addr(tmp.img_ptr, &tmp.bpp, &tmp.line_len, &tmp.endian);

    draw_floor_ceiling(info, &tmp);
    draw_fps(info, &tmp);
    draw_minimap(info, &tmp, minimap_init());
    draw_player_rays(info, &tmp);

    if (info->img.img_ptr != NULL)
    {
        mlx_destroy_image(info->id, info->img.img_ptr);
        info->img.img_ptr = NULL;
    }
    info->img.img_ptr = tmp.img_ptr;
    mlx_put_image_to_window(info->id, info->wd_ptr, info->img.img_ptr, 0, 0);
    return (0);
}
