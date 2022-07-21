/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleroy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 15:21:22 by aleroy            #+#    #+#             */
/*   Updated: 2022/07/21 15:21:24 by aleroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	move_right(float dirx, float diry, t_info *info)
{
	float	tempx;
	float	tempy;

	tempy = info->cast.posy - (MOVESPEED * dirx);
	tempx = info->cast.posx + (MOVESPEED * diry);
	if (info->map[(int)info->cast.posx][(int)tempy] != '1')
		info->cast.posy = tempy;
	if (info->map[(int)tempx][(int)info->cast.posy] != '1')
		info->cast.posx = tempx;
}

void	move_left(float dirx, float diry, t_info *info)
{
	float	tempx;
	float	tempy;

	tempy = info->cast.posy + (MOVESPEED * dirx);
	tempx = info->cast.posx - (MOVESPEED * diry);
	if (info->map[(int)info->cast.posx][(int)tempy] != '1')
		info->cast.posy = tempy;
	if (info->map[(int)tempx][(int)info->cast.posy] != '1')
		info->cast.posx = tempx;
}

void	move_front(float dirx, float diry, t_info *info)
{
	float	tempx;
	float	tempy;

	tempy = info->cast.posy + (MOVESPEED * diry);
	tempx = info->cast.posx + (MOVESPEED * dirx);
	if (info->map[(int)info->cast.posx][(int)tempy] != '1')
		info->cast.posy = tempy;
	if (info->map[(int)tempx][(int)info->cast.posy] != '1')
		info->cast.posx = tempx;
}

void	move_back(float dirx, float diry, t_info *info)
{
	float	tempx;
	float	tempy;

	tempy = info->cast.posy - (MOVESPEED * diry);
	tempx = info->cast.posx - (MOVESPEED * dirx);
	if (info->map[(int)info->cast.posx][(int)tempy] != '1')
		info->cast.posy = tempy;
	if (info->map[(int)tempx][(int)info->cast.posy] != '1')
		info->cast.posx = tempx;
}

void	ft_move(t_info *info)
{
	if (info->key.d == 1)
		move_right(info->cast.dirx, info->cast.diry, info);
	if (info->key.w == 1)
		move_front(info->cast.dirx, info->cast.diry, info);
	if (info->key.a == 1)
		move_left(info->cast.dirx, info->cast.diry, info);
	if (info->key.s == 1)
		move_back(info->cast.dirx, info->cast.diry, info);
	if (info->key.left == 1)
		rotate_left(info);
	if (info->key.right == 1)
		rotate_right(info);
}
