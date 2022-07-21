/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saich <saich@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 16:22:57 by saich             #+#    #+#             */
/*   Updated: 2022/07/19 16:25:27 by saich            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_right(float dirx, float diry, t_info *info)
{
	float	tempx;
	float	tempy;

	tempy = info->cast.posy - (MOVESPEED * dirx);
	tempx = info->cast.posx + (MOVESPEED * diry);
	if ((int)tempy <= 0 || (int)tempy + 1
		>= (int)ft_strlen(info->map[info->cast.mapx]) || (int)tempx <= 0
		|| (int)tempx >= size_map(info->map))
		exit_window(info, "You left the map");
	info->cast.posy = tempy;
	info->cast.posx = tempx;
}

void	move_left(float dirx, float diry, t_info *info)
{
	float	tempx;
	float	tempy;

	tempy = info->cast.posy + (MOVESPEED * dirx);
	tempx = info->cast.posx - (MOVESPEED * diry);
	if ((int)tempy <= 0 || (int)tempy + 1
		>= (int)ft_strlen(info->map[info->cast.mapx]) || (int)tempx <= 0
		|| (int)tempx >= size_map(info->map))
		exit_window(info, "You left the map");
	info->cast.posy = tempy;
	info->cast.posx = tempx;
}

void	move_front(float dirx, float diry, t_info *info)
{
	float	tempx;
	float	tempy;

	tempy = info->cast.posy + (MOVESPEED * diry);
	tempx = info->cast.posx + (MOVESPEED * dirx);
	if ((int)tempy <= 0 || (int)tempy + 1
		>= (int)ft_strlen(info->map[info->cast.mapx]) || (int)tempx <= 0
		|| (int)tempx >= size_map(info->map))
		exit_window(info, "You left the map");
	info->cast.posy = tempy;
	info->cast.posx = tempx;
}

void	move_back(float dirx, float diry, t_info *info)
{
	float	tempx;
	float	tempy;

	tempy = info->cast.posy - (MOVESPEED * diry);
	tempx = info->cast.posx - (MOVESPEED * dirx);
	if ((int)tempy <= 0 || (int)tempy + 1
		>= (int)ft_strlen(info->map[info->cast.mapx]) || (int)tempx <= 0
		|| (int)tempx >= size_map(info->map))
		exit_window(info, "You left the map");
	info->cast.posy = tempy;
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

// void	move_right(float dirx, float diry, t_info *info)
// {
// 	float	tempx;
// 	float	tempy;

// 	tempy = info->cast.posy - (MOVESPEED * dirx);
// 	tempx = info->cast.posx + (MOVESPEED * diry);
// 	if (info->map[(int)info->cast.posx][(int)tempy] != '1')
// 		info->cast.posy = tempy;
// 	if (info->map[(int)tempx][(int)info->cast.posy] != '1')
// 		info->cast.posx = tempx;y
// }

// void	move_left(float dirx, float diry, t_info *info)
// {
// 	float	tempx;
// 	float	tempy;

// 	tempy = info->cast.posy + (MOVESPEED * dirx);
// 	tempx = info->cast.posx - (MOVESPEED * diry);
// 	if (info->map[(int)info->cast.posx][(int)tempy] != '1')
// 		info->cast.posy = tempy;
// 	if (info->map[(int)tempx][(int)info->cast.posy] != '1')
// 		info->cast.posx = tempx;
// }

// void	move_front(float dirx, float diry, t_info *info)
// {
// 	float	tempx;
// 	float	tempy;

// 	tempy = info->cast.posy + (MOVESPEED * diry);
// 	tempx = info->cast.posx + (MOVESPEED * dirx);
// 	if (info->map[(int)info->cast.posx][(int)tempy] != '1')
// 		info->cast.posy = tempy;
// 	if (info->map[(int)tempx][(int)info->cast.posy] != '1')
// 		info->cast.posx = tempx;
// }

// void	move_back(float dirx, float diry, t_info *info)
// {
// 	float	tempx;
// 	float	tempy;

// 	tempy = info->cast.posy - (MOVESPEED * diry);
// 	tempx = info->cast.posx - (MOVESPEED * dirx);
// 	if (info->map[(int)info->cast.posx][(int)tempy] != '1')
// 		info->cast.posy = tempy;
// 	if (info->map[(int)tempx][(int)info->cast.posy] != '1')
// 		info->cast.posx = tempx;
// }

// void	ft_move(t_info *info)
// {
// 	if (info->key.d == 1)
// 		move_right(info->cast.dirx, info->cast.diry, info);
// 	if (info->key.w == 1)
// 		move_front(info->cast.dirx, info->cast.diry, info);
// 	if (info->key.a == 1)
// 		move_left(info->cast.dirx, info->cast.diry, info);
// 	if (info->key.s == 1)
// 		move_back(info->cast.dirx, info->cast.diry, info);
// 	if (info->key.left == 1)
// 		rotate_left(info);
// 	if (info->key.right == 1)
// 		rotate_right(info);
// }
