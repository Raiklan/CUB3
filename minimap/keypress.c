
#include "fdf.h"

int	key_release(int key_sym, t_info *info)
{
	if (key_sym == XK_Escape)
	{
		mlx_destroy_window(info->id, info->wd_ptr);
		info->wd_ptr = NULL;
	}
	//else if(key_sym == 0x77)//w
	//	write(1, "w released\n", 11);
	//else if(key_sym == 0x61)//a
	//	write(1, "a released\n", 11);
	//else if(key_sym == 0x73)//s
	//	write(1, "s released\n", 11);
	//else if(key_sym == 0x64)//d
	//	write(1, "d released\n", 11);
	//else if(key_sym == 0xff51)//left
	//	write(1, "left released\n", 14);
	//else if(key_sym == 0xff53)//right
	//	write(1, "right released\n", 15);
	return (0);
}

void up_down(t_info *info, int key_sym)
{
	if (key_sym == 0x77)//w
	{
		if (info->line[(int)info->player.y / info->tile_size]
			[(int)(info->player.x + info->player.dirx) /
				info->tile_size] == '0')
			info->player.x += info->player.dirx;
		if (info->line[(int)(info->player.y + info->player.diry) /
			info->tile_size][(int)info->player.x / info->tile_size] == '0')
			info->player.y += info->player.diry;
	}
	else if (key_sym == 0x73)//s
	{
		if (info->line[(int)info->player.y / info->tile_size]
			[(int)(info->player.x - info->player.dirx) /
				info->tile_size] == '0')
			info->player.x -= info->player.dirx;
		if (info->line[(int)(info->player.y - info->player.diry) /
			info->tile_size][(int)info->player.x / info->tile_size] == '0')
			info->player.y -= info->player.diry;
	}
}

void	left_right(t_info *info, int key_sym)
{
	if (key_sym == 0x61)//a
	{
		if (info->line[(int)info->player.y / info->tile_size]
			[(int)(info->player.x + info->player.diry) /
				info->tile_size] == '0')
			info->player.x += info->player.diry;
		if (info->line[(int)(info->player.y + (info->player.dirx * -1)) /
			info->tile_size][(int)info->player.x / info->tile_size] == '0')
			info->player.y += info->player.dirx * -1;
	}
	else if (key_sym == 0x64)//d
	{
		if (info->line[(int)info->player.y / info->tile_size]
			[(int)(info->player.x + (info->player.diry * -1)) /
				info->tile_size] == '0')
			info->player.x += info->player.diry * -1;
		if (info->line[(int)(info->player.y + info->player.dirx) /
			info->tile_size][(int)info->player.x / info->tile_size] == '0')
			info->player.y += info->player.dirx;
	}
}

int	key_press(int key_sym, t_info *info)
{
	printf("dirx = %f, diry = %f\n", info->player.dirx ,info->player.diry);
	printf("x = %f, y = %f\n", info->player.x / info->tile_size ,info->player.y / info->tile_size);

	if (key_sym == XK_Escape)
	{
		mlx_destroy_window(info->id, info->wd_ptr);
		info->wd_ptr = NULL;
	}
	else if (key_sym == 0xff51)//left
	{
		info->player.angle -= 0.1;
		if (info->player.angle < 0)
			info->player.angle += 2 * PI;
		info->player.dirx = cos(info->player.angle) * 2;//change the num to change movespeed (pixel)
		info->player.diry = sin(info->player.angle) * 2;
	}
	else if (key_sym == 0xff53)//right
	{
		info->player.angle += 0.1;
		if (info->player.angle > 2 * PI) 
			info->player.angle -= 2 * PI;
		info->player.dirx = cos(info->player.angle) * 2;
		info->player.diry = sin(info->player.angle) * 2;
	}
	up_down(info, key_sym);
	left_right(info, key_sym);
	if (key_sym == 0x77 || key_sym == 0x73 || key_sym == 0x61 || key_sym == 0x64 || key_sym == 0xff51 || key_sym == 0xff53)//can comment this line for norm, not a big deal
		render(info);
	
	printf("after dirx = %f, after diry = %f\n\n", info->player.dirx ,info->player.diry);
	int x;
	int y =0;
	while (info->line[y])
	{
		x =0;
		while (info->line[y][x])
		{
			if ((int)info->player.y / info->tile_size == y && ((int)info->player.x / info->tile_size) == x)
				write(1, "P", 1);
			else
				write(1, &info->line[y][x], 1);
			x++;
		}
		write(1, "\n", 1);
		y++;
	}
	write(1, "\n", 1);
	write(1, "--------------------------------------------------------------------------------\n", 81);
	write(1, "\n", 1);
	return (0);
}





/*int	key_release(int key_sym, t_info *info)
{
	if (key_sym == XK_Escape)
	{
		mlx_destroy_window(info->id, info->wd_ptr);
		info->wd_ptr = NULL;
	}
	//else if(key_sym == 0x7a)//z
	//	write(1, "z released\n", 11);
	//else if(key_sym == 0x71)//q
	//	write(1, "q released\n", 11);
	//else if(key_sym == 0x73)//s
	//	write(1, "s released\n", 11);
	//else if(key_sym == 0x64)//d
	//	write(1, "d released\n", 11);
	//else if(key_sym == 0xff51)//left
	//	write(1, "left released\n", 14);
	//else if(key_sym == 0xff53)//right
	//	write(1, "right released\n", 15);
	return (0);
}

void up_down(t_info *info, int key_sym)
{
	if (key_sym == 0x7a)//z
	{
		if (info->line[(int)info->player.y / info->tile_size]
			[(int)(info->player.x + info->player.dirx) /
				info->tile_size] == '0')
			info->player.x += info->player.dirx;
		if (info->line[(int)(info->player.y + info->player.diry) /
			info->tile_size][(int)info->player.x / info->tile_size] == '0')
			info->player.y += info->player.diry;
	}
	else if (key_sym == 0x73)//s
	{
		if (info->line[(int)info->player.y / info->tile_size]
			[(int)(info->player.x - info->player.dirx) /
				info->tile_size] == '0')
			info->player.x -= info->player.dirx;
		if (info->line[(int)(info->player.y - info->player.diry) /
			info->tile_size][(int)info->player.x / info->tile_size] == '0')
			info->player.y -= info->player.diry;
	}
}

void	left_right(t_info *info, int key_sym)
{
	if (key_sym == 0x71)//q
	{
		if (info->line[(int)info->player.y / info->tile_size]
			[(int)(info->player.x + info->player.diry) /
				info->tile_size] == '0')
			info->player.x += info->player.diry;
		if (info->line[(int)(info->player.y + (info->player.dirx * -1)) /
			info->tile_size][(int)info->player.x / info->tile_size] == '0')
			info->player.y += info->player.dirx * -1;
	}
	else if (key_sym == 0x64)//d
	{
		if (info->line[(int)info->player.y / info->tile_size]
			[(int)(info->player.x + (info->player.diry * -1)) /
				info->tile_size] == '0')
			info->player.x += info->player.diry * -1;
		if (info->line[(int)(info->player.y + info->player.dirx) /
			info->tile_size][(int)info->player.x / info->tile_size] == '0')
			info->player.y += info->player.dirx;
	}
}

int	key_press(int key_sym, t_info *info)
{
	printf("dirx = %f, diry = %f\n", info->player.dirx ,info->player.diry);
	printf("x = %f, y = %f\n", info->player.x / info->tile_size ,info->player.y / info->tile_size);

	if (key_sym == XK_Escape)
	{
		mlx_destroy_window(info->id, info->wd_ptr);
		info->wd_ptr = NULL;
	}
	else if (key_sym == 0xff51)//left
	{
		info->player.angle -= 0.1;
		if (info->player.angle < 0)
			info->player.angle += 2 * PI;
		info->player.dirx = cos(info->player.angle) * 5;
		info->player.diry = sin(info->player.angle) * 5;
	}
	else if (key_sym == 0xff53)//right
	{
		info->player.angle += 0.1;
		if (info->player.angle > 2 * PI) 
			info->player.angle -= 2 * PI;
		info->player.dirx = cos(info->player.angle) * 5;
		info->player.diry = sin(info->player.angle) * 5;
	}
	up_down(info, key_sym);
	left_right(info, key_sym);
	if (key_sym == 0x7a || key_sym == 0x73 || key_sym == 0x71 || key_sym == 0x64 || key_sym == 0xff51 || key_sym == 0xff53)//can comment this line for norm, not a big deal
		render(info);
	
	printf("after dirx = %f, after diry = %f\n\n", info->player.dirx ,info->player.diry);
	int x;
	int y =0;
	while (info->line[y])
	{
		x =0;
		while (info->line[y][x])
		{
			if ((int)info->player.y / info->tile_size == y && ((int)info->player.x / info->tile_size) == x)
				write(1, "P", 1);
			else
				write(1, &info->line[y][x], 1);
			x++;
		}
		write(1, "\n", 1);
		y++;
	}
	write(1, "\n", 1);
	write(1, "--------------------------------------------------------------------------------\n", 81);
	write(1, "\n", 1);
	return (0);
}*/

int	handle_no_event(void)
{
	return (0);
}
