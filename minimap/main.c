/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleroy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 12:51:17 by aleroy            #+#    #+#             */
/*   Updated: 2022/01/05 12:51:21 by aleroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

void	img_pix_put(t_info *info, t_img *img, int x, int y)
{
	char	*pixel;

	if (y < 0 || y > info->wd_height)
		return ;
	if (x > info->wd_width && y >= info->wd_height)
		return ;
	if (x < 0 && y <= 0)
		return ;
	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(int *)pixel = info->color;
}

int	key_release(int key_sym, t_info *info)
{
	if (key_sym == XK_Escape)
	{
		mlx_destroy_window(info->id, info->wd_ptr);
		info->wd_ptr = NULL;
	}
	else if(key_sym == 0x77)//w
		write(1, "w released\n", 11);
	else if(key_sym == 0x61)//a
		write(1, "a released\n", 11);
	else if(key_sym == 0x73)//s
		write(1, "s released\n", 11);
	else if(key_sym == 0x64)//d
		write(1, "d released\n", 11);
	else if(key_sym == 0xff51)//left
		write(1, "left released\n", 14);
	else if(key_sym == 0xff53)//right
		write(1, "right released\n", 15);
	return (0);
}

int	key_press(int key_sym, t_info *info)
{
	double oldx;

	if (key_sym == XK_Escape)
	{
		mlx_destroy_window(info->id, info->wd_ptr);
		info->wd_ptr = NULL;
	}
	else if(key_sym == 0x77)//w
	{
		info->player.x += info->tile_size / 3 * info->player.dirx;
		info->player.y += info->tile_size / 3 * info->player.diry;
		write(1, "z pressed\n", 10);
		render(info, info->line);
	}
	else if(key_sym == 0x61)//a
	{
		info->player.x += info->tile_size / 3 * info->player.diry;
		info->player.y += info->tile_size / 3 * info->player.dirx * -1;
		write(1, "q pressed\n", 10);
		render(info, info->line);
	}
	else if(key_sym == 0x73)//s
	{
		info->player.x -= info->tile_size / 3 * info->player.dirx;
		info->player.y -= info->tile_size / 3 * info->player.diry;
		write(1, "s pressed\n", 10);
		render(info, info->line);
	}
	else if(key_sym == 0x64)//d
	{
		info->player.x += info->tile_size / 3 * info->player.diry * -1;
		info->player.y += info->tile_size / 3 * info->player.dirx;
		write(1, "d pressed\n", 10);
		render(info, info->line);
	}
	else if(key_sym == 0xff51)//left
	{
		//printf("dirx = %f, diry = %f\n", info->player.dirx = info->player.dirx ,info->player.diry);
		oldx = info->player.dirx * -1;
		info->player.dirx = info->player.diry;
		info->player.diry = oldx;
		//printf("after dirx = %f, after diry = %f\n", info->player.dirx = info->player.dirx ,info->player.diry);
		write(1, "left pressed\n", 13);
		render(info, info->line);
	}
	else if(key_sym == 0xff53)//right
	{
		//printf("dirx = %f, diry = %f\n", info->player.dirx = info->player.dirx ,info->player.diry);
		oldx = info->player.dirx;
		info->player.dirx = info->player.diry * -1;
		info->player.diry = oldx;
		//printf("after dirx = %f, after diry = %f\n", info->player.dirx = info->player.dirx ,info->player.diry);
		write(1, "right pressed\n", 14);
		render(info, info->line);
	}
	return (0);
}

/*int	key_release(int key_sym, t_info *info)
{
	if (key_sym == XK_Escape)
	{
		mlx_destroy_window(info->id, info->wd_ptr);
		info->wd_ptr = NULL;
	}
	else if(key_sym == 0x7a)//z
		write(1, "z released\n", 11);
	else if(key_sym == 0x71)//q
		write(1, "q released\n", 11);
	else if(key_sym == 0x73)//s
		write(1, "s released\n", 11);
	else if(key_sym == 0x64)//d
		write(1, "d released\n", 11);
	else if(key_sym == 0xff51)//left
		write(1, "left released\n", 14);
	else if(key_sym == 0xff53)//right
		write(1, "right released\n", 15);
	return (0);
}

int	key_press(int key_sym, t_info *info)
{
	double oldx;

	if (key_sym == XK_Escape)
	{
		mlx_destroy_window(info->id, info->wd_ptr);
		info->wd_ptr = NULL;
	}
	else if(key_sym == 0x7a)//z
	{
		info->player.x += info->tile_size / 3 * info->player.dirx;
		info->player.y += info->tile_size / 3 * info->player.diry;
		write(1, "z pressed\n", 10);
		render(info, info->line);
	}
	else if(key_sym == 0x71)//q
	{
		info->player.x += info->tile_size / 3 * info->player.diry;
		info->player.y += info->tile_size / 3 * info->player.dirx * -1;
		write(1, "q pressed\n", 10);
		render(info, info->line);
	}
	else if(key_sym == 0x73)//s
	{
		info->player.x -= info->tile_size / 3 * info->player.dirx;
		info->player.y -= info->tile_size / 3 * info->player.diry;
		write(1, "s pressed\n", 10);
		render(info, info->line);
	}
	else if(key_sym == 0x64)//d
	{
		info->player.x += info->tile_size / 3 * info->player.diry * -1;
		info->player.y += info->tile_size / 3 * info->player.dirx;
		write(1, "d pressed\n", 10);
		render(info, info->line);
	}
	else if(key_sym == 0xff51)//left
	{
		//printf("dirx = %f, diry = %f\n", info->player.dirx = info->player.dirx ,info->player.diry);
		oldx = info->player.dirx * -1;
		info->player.dirx = info->player.diry;
		info->player.diry = oldx;
		//printf("after dirx = %f, after diry = %f\n", info->player.dirx = info->player.dirx ,info->player.diry);
		write(1, "left pressed\n", 13);
		render(info, info->line);
	}
	else if(key_sym == 0xff53)//right
	{
		//printf("dirx = %f, diry = %f\n", info->player.dirx = info->player.dirx ,info->player.diry);
		oldx = info->player.dirx;
		info->player.dirx = info->player.diry * -1;
		info->player.diry = oldx;
		//printf("after dirx = %f, after diry = %f\n", info->player.dirx = info->player.dirx ,info->player.diry);
		write(1, "right pressed\n", 14);
		render(info, info->line);
	}
	return (0);
}*/

int	handle_no_event(void)
{
	return (0);
}

int	destroyer(t_info *info, char **line)
{
	destroyer2(info);
	write(1, "destroyer called\n", 17);
	int	i;

	i = 0;
	while (line && line[i] != NULL)
	{
		free(line[i]);
		i++;
	}
	if (line != NULL)
		free(line);
	free(info->id);
	free(info->wd_ptr);
	write(1, "destroyer finished\n", 19);
	exit(0);
	return (-1);
}

int	destroyer2(t_info *info)
{
	write(1, "destroyer called\n", 17);
	if (info->img.img_ptr != NULL)
		mlx_destroy_image(info->id, info->img.img_ptr);
	mlx_destroy_display(info->id);
	write(1, "destroyer finished\n", 19);
	return (0);
}

int	main(int argc, char **argv)
{
	t_info	info;
	char	**line;

	line = main_2(argc, argv, &info);
	if (line == NULL)
		return (-1);
	info.line = line;
	info.id = mlx_init();
	if (info.id == NULL)
		return (-1);
	info.wd_ptr = mlx_new_window(info.id, info.wd_width, info.wd_height,
			"fdf" );
	if (info.wd_ptr == NULL)
		return (-1);

	if (render(&info, line) == -1)
		return (destroyer(&info, line));
	mlx_loop_hook(info.id, &handle_no_event, &info);
	mlx_hook(info.wd_ptr, KeyPress, KeyPressMask, &key_press, &info);
	mlx_hook(info.wd_ptr, KeyRelease, KeyReleaseMask, &key_release, &info);
	mlx_hook(info.wd_ptr, 33, 1L << 5, &destroyer2, &info);
	mlx_loop(info.id);
	destroyer(&info, line);
	return (0);
}
