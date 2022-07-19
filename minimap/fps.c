//header

#include "fdf.h"

void	draw_floor_ceiling(t_info *info, t_img *tmp)
{
	int	i;
	int	j;

	j = 0;
	info->color = info->ceiling;
	while (j < info->wd_height)
	{
		i = 0;
		while (i < info->wd_width)
		{
			img_pix_put(info, tmp, i, j);
			i++;
		}
		j++;
		if (j == info->wd_height / 2)
			info->color = info->floor;
	}
}

void	draw_fps(t_info *info, t_img *tmp)
{
	t_raycast	raycast;
	int x;
	int test;
	t_coor	coor;

	coor.tile_size = info->tile_size;
	raycast.rangle = info->player.angle - (DEGREE * 30);
	raycast.rays = 0;
	x = 0;
	while (raycast.rays < 60)
	{
		test = 0;
		info->color = 0x0000ff;
		init_rays_stuff(info, &raycast);
		get_rays_step_dir(info, &raycast);
		get_wall_contact(info, &raycast);
		get_wall_heigth(info, &raycast);

		// if (side == 1 && rangle >= PI && (rangle <= PI * 2 || rangle <= 0))
		// 	printf("N\n");
		// else if (side == 1 && rangle >= 0 && rangle <= PI)
		// 	printf("S\n");
		
		// if (side == 0 && rangle >= PI / 2 && rangle <= (3 * PI) / 2)
		// 	printf("W\n");
		// else if (side == 0)
		// 	printf("E\n");

		if (raycast.side == 0)
			info->color /= 2;
		while (test < 8)
		{
			coor.x1 = x;
			coor.y1 = raycast.drawStart;
			coor.xold = x;
			coor.yold = raycast.drawEnd;
			bresenham_new(info, tmp, &coor, raycast.side);
			test++;
			x++;
		}
		raycast.rays++;
		raycast.rangle += DEGREE;
	}
}
