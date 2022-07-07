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

void	draw_player(t_info *info, t_img *tmp)
{
	int rayx;
	int rayy;
	double ray_dirx;
	double ray_diry;
	double next_full_x;
	double next_full_y;
	double le_restex;
	double le_restey;
	int stepx;
	int stepy;
	bool wall_hit;
	bool side;

	t_coor	coor;

	info->color = 0x0000ff;
	coor.tile_size = info->tile_size;


	float rangle = info->player.angle - (DEGREE * 30);
	int rays = 0;
	while (rays < 60)
	{
		if (rangle < 0)
			rangle += 2 * PI;
		if (rangle > 2 * PI)
			rangle -= 2 * PI;


		rayx = info->player.x;
		rayy = info->player.y;


		ray_dirx = cos(rangle) * 5;//add camera/plane??
		ray_diry = sin(rangle) * 5;
		wall_hit = 0;


		if (ray_dirx == 0)
			next_full_x = 1e30;
		else
			next_full_x = sqrt(1 + (ray_diry * ray_diry) / (ray_dirx * ray_dirx));
		if (ray_diry == 0)
			next_full_y = 1e30;
		else
			next_full_y = sqrt(1 + (ray_dirx * ray_dirx) / (ray_diry * ray_diry));


		if (ray_dirx < 0)
		{
			stepx = -1;
			le_restex = (info->player.x - rayx) * next_full_x;
		}
		else
		{
			stepx = 1;
			le_restex = (rayx + 1.0 - info->player.x) * next_full_x;
		}
		if (ray_diry < 0)
		{
			stepy = -1;
			le_restey = (info->player.y - rayy) * next_full_y;
		}
		else
		{
			stepy = 1;
			le_restey = (rayy + 1.0 - info->player.y) * next_full_y;
		}



		while (wall_hit == 0)
		{
			if (le_restex < le_restey)
			{
				le_restex += next_full_x;
				rayx += stepx;
				side = 0;//x side
			}
			else
			{
				le_restey += next_full_y;
				rayy += stepy;
				side = 1;// y side
			}
			if (info->line[rayy/ info->tile_size][rayx/ info->tile_size] == '1')
				wall_hit = 1;
		}


		if (side == 1 && rangle >= PI && (rangle <= PI * 2 || rangle <= 0))
			printf("N\n");
		else if (side == 1 && rangle >= 0 && rangle <= PI)
			printf("S\n");
		
		if (side == 0 && rangle >= PI / 2 && rangle <= (3 * PI) / 2)
			printf("W\n");
		else if (side == 0)
			printf("E\n");

		rays++;
		coor.x1 = rayx;
		coor.y1 = rayy;
		coor.xold = info->player.x;
		coor.yold = info->player.y;
		bresenham_new(info, tmp, &coor);
		rangle += DEGREE;
	}

	//t_coor coor;

	info->color = 0xff0000;
	coor.x1 = info->player.x + info->player.dirx * 5;
	coor.y1 = info->player.y + info->player.diry * 5;
	coor.xold = info->player.x;
	coor.yold = info->player.y;
	bresenham_new(info, tmp, &coor);
	info->color = 0xff0000;
	img_pix_put(info, tmp, info->player.x, info->player.y);
}

void	draw_minimap(t_info *info, t_img *tmp, int x, int y)
{
	int	i;
	int	j;
	int	pixel_count;
	int	col_count;

	i = 0;
	while (info->line[i])
    {
        col_count = 0;
        while (col_count < info->tile_size)
        {
            j = 0;
            while (info->line[i][j])
            {
                pixel_count = 0;
                while (pixel_count < info->tile_size)
                {
                    if (pixel_count == 0 || col_count == 0)
                        info->color = 0x0;
                    else if (pixel_count + 1 == info->tile_size || col_count + 1 == info->tile_size)
                    	info->color = 0xffffff;
                    else if (info->line[i][j] == '0')
                        info->color = 0xbdb76b;
                    else if (info->line[i][j] == '\t' || info->line[i][j] == ' ')
                        info->color = 0xcccccc;//{ "grey80" , 0xcccccc },
                    else
                        info->color = 0x696969;
                    img_pix_put(info, tmp, x, y);
                    pixel_count++;
                    x++;
                }
                j++;
            }
            y++;
            col_count++;
            x = 0;
        }
        i++;
    }
}

int    render(t_info *info)
{
    t_img    tmp;

    tmp.img_ptr = mlx_new_image(info->id, info->wd_width, info->wd_height);
    if (tmp.img_ptr == NULL)
        return (destroyer(info, info->line));
    tmp.addr = mlx_get_data_addr(tmp.img_ptr, &tmp.bpp, &tmp.line_len, &tmp.endian);
    info->color = 0x0;
    clear_background(info, &tmp);

    draw_minimap(info, &tmp, 0, 0);

    draw_player(info, &tmp);
    if (info->img.img_ptr != NULL)
    {
        mlx_destroy_image(info->id, info->img.img_ptr);
        info->img.img_ptr = NULL;
    }
    info->img.img_ptr = tmp.img_ptr;
    mlx_put_image_to_window(info->id, info->wd_ptr, info->img.img_ptr, 0, 0);
    return (0);
}
