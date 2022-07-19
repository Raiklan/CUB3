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


	info.texture.tex_ptr = mlx_xpm_file_to_image(info.id, "./backroom_wallpaper.xpm", &info.texture.texture_width, &info.texture.texture_height);
	if (info.texture.tex_ptr == NULL)
    	exit(-1);
	info.texture.addr = mlx_get_data_addr(info.texture.tex_ptr, &info.texture.bpp, &info.texture.line_len, &info.texture.endian);
   	info.texture.x = 0;
   	info.texture.y = 0;
	

	if (render(&info) == -1)
		return (destroyer(&info, line));
	mlx_loop_hook(info.id, &handle_no_event, &info);
	mlx_hook(info.wd_ptr, KeyPress, KeyPressMask, &key_press, &info);
	mlx_hook(info.wd_ptr, KeyRelease, KeyReleaseMask, &key_release, &info);
	mlx_hook(info.wd_ptr, 33, 1L << 5, &destroyer2, &info);
	mlx_loop(info.id);
	destroyer(&info, line);
	return (0);
}
