/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_view.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saich <saich@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 16:14:32 by saich             #+#    #+#             */
/*   Updated: 2022/07/21 16:14:46 by saich            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	setup_view(t_info *info)
{
	if ((int)info->env.pos_dir == 'N')
	{
		info->cast.dirx = -1;
		info->cast.plany = 0.66;
	}
	else if ((int)info->env.pos_dir == 'S')
	{
		info->cast.dirx = 1;
		info->cast.plany = -0.66;
	}
	else if ((int)info->env.pos_dir == 'E')
	{
		info->cast.diry = 1;
		info->cast.planx = 0.66;
	}
	else if ((int)info->env.pos_dir == 'W')
	{
		info->cast.diry = -1;
		info->cast.planx = -0.66;
	}
}

void	init_struct(t_info *info)
{
	ft_bzero(&info->cast, sizeof(info->cast));
	info->cast.posx = info->env.pos_coor[0] + 0.5;
	info->cast.posy = info->env.pos_coor[1] + 0.5;
	info->cast.mapx = (int)info->env.pos_coor[0];
	info->cast.mapy = (int)info->env.pos_coor[1];
	setup_view(info);
}

int	print_error(char *str)
{
	write(2, "Error\n", 6);
	write(2, str, ft_strlen(str));
	return (1);
}
