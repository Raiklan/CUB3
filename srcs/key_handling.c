/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleroy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 15:58:10 by aleroy            #+#    #+#             */
/*   Updated: 2022/06/10 15:58:13 by aleroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "cub3d.h"
#include <stdlib.h>
#include <unistd.h>
#include <X11/keysym.h>
# include "../mlx_linux/mlx.h"

typedef struct s_info
{
	void	*id;
	void	*wd_ptr;
}				t_info;


int	handle_event(int key_sym, t_info *info)
{
	if (key_sym == XK_Escape)
	{
		mlx_destroy_window(info->id, info->wd_ptr);
		info->wd_ptr = NULL;
	}
	else if(key_sym == 0x77)//w
		write(1, "w\n", 2);
	else if(key_sym == 0x61)//a
		write(1, "a\n", 2);
	else if(key_sym == 0x73)//s
		write(1, "s\n", 2);
	else if(key_sym == 0x64)//d
		write(1, "d\n", 2);
	else if(key_sym == 0xff51)//left
		write(1, "left\n", 5);
	else if(key_sym == 0xff53)//right
		write(1, "right\n", 6);
	return (0);
}

int	handle_no_event(void)
{
	return (0);
}

void destroyer(t_info *info)
{
	mlx_destroy_display(info->id);
	free(info->id);
	free(info->wd_ptr);
}

int	main(int argc, char **argv)
{
	(void)argv;
	(void)argc;
	t_info	info;

	info.id = mlx_init();
	if (info.id == NULL)
		return (-1);
	info.wd_ptr = mlx_new_window(info.id, 700, 500,
			"cub3d" );
	if (info.wd_ptr == NULL)
		return (-1);
	mlx_loop_hook(info.id, &handle_no_event, &info);
	mlx_key_hook(info.wd_ptr, &handle_event, &info);
	mlx_loop(info.id);
	destroyer(&info);
	return (0);
}
