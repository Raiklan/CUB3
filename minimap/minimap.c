//header

#include "fdf.h"

void	draw_player_rays(t_info *info, t_img *tmp)
{
	t_raycast	raycast;
	t_coor		coor;

	coor.tile_size = info->tile_size;
	raycast.rangle = info->player.angle - (DEGREE * info->fov / 2);
	raycast.rays = 0;
	while (raycast.rays < info->fov)
	{
		info->color = 0x0000ff;
		init_rays_stuff(info, &raycast);
		get_rays_step_dir(info, &raycast);
		get_wall_contact(info, &raycast);
		if (raycast.side == 0)
			info->color /= 2;
		coor.x1 = raycast.rayx;
		coor.y1 = raycast.rayy;
		coor.xold = info->player.x;
		coor.yold = info->player.y;
		bresenham_new(info, tmp, &coor, -1);
		raycast.rays++;
		raycast.rangle += DEGREE;
	}
	draw_player(info, tmp);
}

void	draw_player(t_info *info, t_img *tmp)
{
	t_coor	coor;

	info->color = 0xff0000;
	coor.x1 = info->player.x + info->player.dirx * 3;
	coor.y1 = info->player.y + info->player.diry * 3;
	coor.xold = info->player.x;
	coor.yold = info->player.y;
	bresenham_new(info, tmp, &coor, -1);
	coor.x1 = info->player.x - info->player.diry * 3;//right
	coor.y1 = info->player.y + info->player.dirx * 3;
	coor.xold = info->player.x;
	coor.yold = info->player.y;
	bresenham_new(info, tmp, &coor, -1);
	coor.x1 = info->player.x + info->player.diry * 3;//left
	coor.y1 = info->player.y - info->player.dirx * 3;
	coor.xold = info->player.x;
	coor.yold = info->player.y;
	bresenham_new(info, tmp, &coor, -1);
}

t_minimap	minimap_init()
{
	t_minimap	tmp;

	tmp.x = 0;
	tmp.y = 0;
	tmp.i = 0;
	return (tmp);
}

void	chose_minimap_color(t_info *info, t_minimap *minimap)
{
	if (minimap->pixel_count == 0 || minimap->col_count == 0)
        info->color = 0x0;
    else if (minimap->pixel_count + 1 == info->tile_size ||
    	minimap->col_count + 1 == info->tile_size)
    	info->color = 0xffffff;
    else if (info->line[minimap->i][minimap->j] == '0')
        info->color = 0xbdb76b;
    else if (info->line[minimap->i][minimap->j] == '\t' ||
    	info->line[minimap->i][minimap->j] == ' ')
        info->color = 0xcccccc;
    else
        info->color = 0x696969;
}

void	draw_minimap(t_info *info, t_img *tmp, t_minimap minimap)
{
	while (info->line[minimap.i])
    {
        minimap.col_count = 0;
        while (minimap.col_count < info->tile_size)
        {
            minimap.j = 0;
            while (info->line[minimap.i][minimap.j])
            {
               minimap.pixel_count = 0;
                while (minimap.pixel_count < info->tile_size)
                {
                    chose_minimap_color(info, &minimap);
                    img_pix_put(info, tmp, minimap.x, minimap.y);
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
}
