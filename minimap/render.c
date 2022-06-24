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
	t_coor	coor;

	info->color = 0x0000ff;
	coor.tile_size = info->tile_size;
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
