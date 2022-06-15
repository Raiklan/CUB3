/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleroy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 19:11:11 by aleroy            #+#    #+#             */
/*   Updated: 2022/01/04 19:11:12 by aleroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	clear_background(t_info *info, t_img *tmp)
{
	int	i;
	int	j;

	j = 0;
	while (j < info->wd_height)
	{
		i = 0;
		while (i < info->wd_width)
		{
			img_pix_put(info, tmp, i, j);
			i++;
		}
		j++;
	}
}

void	set_coor(t_info *info, t_coor *coor)
{
	coor->tile_size = info->tile_size;
	coor->x1 = 0;
	coor->y1 = 0;
	coor->z1 = 0;
	coor->xold = 0;
	coor->yold = 0;
	coor->zold = 0;
	coor->_2dx1 = 0;
	coor->_2dy1 = 0;
	coor->_2dxold = 0;
	coor->_2dyold = 0;
}
