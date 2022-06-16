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

void draw_grid(t_info *info, t_img *tmp)
{
	int	i;
	int	j;

	j = 0;
	info->color = 0xf08080;
	while (j < info->wd_height)
	{
		i = 0;
		while (i < info->wd_width)
		{
			if (i % 30 == 0 || j % 30 == 0)
				img_pix_put(info, tmp, i, j);
			i++;
		}
		j++;
	}
}

void	draw_pointer(t_info *info, t_img *tmp, int x, int y)
{
	int i;

	i = 0;
	info->color = 0xee82ee;
	while (i < 20)
	{
		img_pix_put(info, tmp, x, y);
		x += info->player.dirx;
		y += info->player.diry;
		i++;
	}
	info->color = 0xffffff;
}

void	draw_player(t_info *info, t_img *tmp)
{
	int		x;
	int		y;
	int		pixel_count;
	int		col_count;

	x = info->player.x + info->tile_size / 3;
	y = info->player.y + info->tile_size / 3;
	info->color = 0xffffff;
	col_count = 0;
	while (col_count < info->tile_size / 3)
	{
		pixel_count = 0;
		while (pixel_count < info->tile_size / 3)
		{
			img_pix_put(info, tmp, x, y);
			pixel_count++;
			x++;
		}
		y++;
		col_count++;
		x = info->player.x + info->tile_size / 3;
	}
	draw_pointer(info, tmp, info->player.x + info->tile_size / 2, info->player.y + info->tile_size / 2);
}

int	render(t_info *info, char **line)
{
	t_coor	coor;
	int		i;
	int		j;
	int		pixel_count;
	int		col_count;
	t_img	tmp;

	i = 0;
	tmp.img_ptr = mlx_new_image(info->id, info->wd_width, info->wd_height);
	if (tmp.img_ptr == NULL)
		return (destroyer(info, line));
	tmp.addr = mlx_get_data_addr(tmp.img_ptr, &tmp.bpp, &tmp.line_len, &tmp.endian);
	set_coor(info, &coor);
	info->color = 0x0;
	clear_background(info, &tmp);
	info->color = 0xffffff;
	while (line[i])
	{
		col_count = 0;
		while (col_count < info->tile_size)
		{
			j = 0;
			while (line[i][j])
			{
				pixel_count = 0;
				if (line[i][j] == '0')
					info->color = 0xbdb76b;
				else if (line[i][j] == 'N' || line[i][j] == 'S' || line[i][j] == 'E' || line[i][j] == 'W')
					info->color = 0x0000ff;
				else if (line[i][j] == '\t' || line[i][j] == ' ')
					info->color = 0x0;
				else
					info->color = 0x696969;
				while (pixel_count < info->tile_size)
				{
					img_pix_put(info, &tmp, coor.x1, coor.y1);
					pixel_count++;
					coor.x1++;
				}
				j++;
			}
			coor.y1++;
			col_count++;
			coor.x1 = 0;
		}
		i++;
	}
	draw_grid(info, &tmp);
	draw_player(info, &tmp);
	if (info->img.img_ptr != NULL)
	{
		mlx_destroy_image(info->id, info->img.img_ptr);
		info->img.img_ptr = NULL;
	}
	info->img.img_ptr = tmp.img_ptr;
	write (1, "here\n", 5);

	mlx_put_image_to_window(info->id, info->wd_ptr, info->img.img_ptr, 0, 0);
	return (0);
}
