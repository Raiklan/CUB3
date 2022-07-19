/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saich <saich@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 15:30:41 by saich             #+#    #+#             */
/*   Updated: 2022/07/19 15:32:48 by saich            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_number(int key, t_info *info)
{
	(void)info;
	if (key == 119)
		info->key.w = 1;
	if (key == 115)
		info->key.s = 1;
	if (key == 97)
		info->key.a = 1;
	if (key == 100)
		info->key.d = 1;
	if (key == 65361)
		info->key.left = 1;
	if (key == 65363)
		info->key.right = 1;
	if (key == 65307)
		exit_window(info, "program leave successfully");
	return (0);
}

int	push_nbr(int key, t_info *info)
{
	if (key == 119)
		info->key.w = 0;
	if (key == 115)
		info->key.s = 0;
	if (key == 97)
		info->key.a = 0;
	if (key == 100)
		info->key.d = 0;
	if (key == 65361)
		info->key.left = 0;
	if (key == 65363)
		info->key.right = 0;
	return (0);
}
