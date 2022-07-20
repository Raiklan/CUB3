/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saich <saich@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 17:26:38 by saich             #+#    #+#             */
/*   Updated: 2022/07/20 18:51:47 by saich            ###   ########.fr       */
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

void	cub3d(t_info *info)
{
	init_struct(info);
	info->mlx.mlx_ptr = mlx_init();
	get_all_texture(info);
	info->mlx.img_ptr = mlx_new_image(info->mlx.mlx_ptr, info->resolution.x,
			info->resolution.y);
	info->mlx.img_addr = (unsigned int *)mlx_get_data_addr(info->mlx.img_ptr,
			&(info->mlx.bpp), &(info->mlx.size_line), &(info->mlx.endian));
	info->mlx.win_ptr = mlx_new_window(info->mlx.mlx_ptr, info->resolution.x,
			info->resolution.y, "CUB3D");
	mlx_hook(info->mlx.win_ptr, 17, 0L, leave_prog, info);
	mlx_hook(info->mlx.win_ptr, 3, (1L << 1), push_nbr, info);
	mlx_hook(info->mlx.win_ptr, 2, (1L << 0), get_number, info);
	mlx_loop_hook(info->mlx.mlx_ptr, raycasting, info);
	mlx_loop(info->mlx.mlx_ptr);
}

int	check_cub_ext(char **av)
{
	char	*str;

	str = ft_strrchr(av[1], '.');
	if (str == NULL)
		return (print_error("Not a .cub extension for configuration file\n"));
	str++;
	if (*str == 'c')
	{
		str++;
		if (*str == 'u')
		{
			str++;
			if (*str == 'b')
			{
				str++;
				if (*str == '\0')
					return (0);
			}
		}
	}
	return (print_error("Not a .cub extension for configuration file\n"));
}

int	check_cub_rights(char **av)
{
	int	fd;
	int	fd2;

	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		return (print_error("Couldn't open file\n"));
	close(fd);
	fd2 = open(av[1], __O_DIRECTORY);
	if (fd2 != -1)
	{
		close(fd2);
		return (print_error("file is a directory\n"));
	}
	return (0);
}

/* List of all the content of file and verification there isn't 
two instances of the same data*/
int	get_info(char **av, t_info	*info)
{
	int		fd;
	char	*ret;
	t_list	*elem;

	fd = open(av[1], O_RDONLY);
	ret = get_next_line(fd);
	while (ret != NULL)
	{
		elem = ft_lstnew(ret);
		if (!(elem))
			return (print_error(strerror(errno)));
		ft_lstadd_back(info->lst, elem);
		ret = get_next_line(fd);
	}
	close (fd);
	return (0);
}

int	main(int ac, char **av)
{
	t_info	*info;

	info = init_info();
	if (!info || !info->lst)
		return (EXIT_FAILURE);
	if (ac != 2)
	{
		print_error("Not enough arguments: you must include a .cub file for \
configuration of the map !\n");
		return (EXIT_FAILURE);
	}
	if (check_cub_ext(av))
		return (EXIT_FAILURE);
	if (check_cub_rights(av))
		return (EXIT_FAILURE);
	if (get_info(av, info))
		return (EXIT_FAILURE);
	check_content(info);
	cub3d(info);
	return (0);
}
