/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saich <saich@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 15:19:56 by saich             #+#    #+#             */
/*   Updated: 2022/07/19 16:40:52 by saich            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_texture(t_texture *tex, t_info *info)
{
	tex->tex_ptr = mlx_xpm_file_to_image(info->mlx.mlx_ptr,
			tex->path, &tex->w, &tex->h);
	if (!(tex->tex_ptr))
		exit_window(info, "Error\nTexture failed");
	tex->tex_addr = (unsigned int *)mlx_get_data_addr(tex->tex_ptr,
			&(tex->bpp), &(tex->size_line), &(info->mlx.bpp));
}

void	get_all_texture(t_info	*info)
{
	get_texture(&info->env.wall_no, info);
	get_texture(&info->env.wall_so, info);
	get_texture(&info->env.wall_ea, info);
	get_texture(&info->env.wall_we, info);
}
