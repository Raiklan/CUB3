/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saich <saich@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 16:14:31 by saich             #+#    #+#             */
/*   Updated: 2022/07/19 16:16:44 by saich            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_right(t_info *info)
{
	float	old_dir;
	float	old_planx;

	old_dir = info->cast.dirx;
	old_planx = info->cast.planx;
	info->cast.dirx = info->cast.dirx * cos(-ROTATESPEED) - info->cast.diry
		* sin(-ROTATESPEED);
	info->cast.diry = old_dir * sin(-ROTATESPEED) + info->cast.diry
		* cos(-ROTATESPEED);
	info->cast.planx = info->cast.planx * cos(-ROTATESPEED)
		- info->cast.plany * sin(-ROTATESPEED);
	info->cast.plany = old_planx * sin(-ROTATESPEED) + info->cast.plany
		* cos(-ROTATESPEED);
}

void	rotate_left(t_info *info)
{
	float	old_dir;
	float	old_planx;

	old_dir = info->cast.dirx;
	old_planx = info->cast.planx;
	info->cast.dirx = info->cast.dirx * cos(ROTATESPEED) - info->cast.diry
		* sin(ROTATESPEED);
	info->cast.diry = old_dir * sin(ROTATESPEED) + info->cast.diry
		* cos(ROTATESPEED);
	info->cast.planx = info->cast.planx * cos(ROTATESPEED) - info->cast.plany
		* sin(ROTATESPEED);
	info->cast.plany = old_planx * sin(ROTATESPEED) + info->cast.plany
		* cos(ROTATESPEED);
}

