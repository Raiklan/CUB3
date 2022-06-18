/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_wd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleroy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 19:07:16 by aleroy            #+#    #+#             */
/*   Updated: 2022/01/04 19:07:19 by aleroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

char	**prep_line(int fd, char *buf, char *line, char *tmp)
{
	char	**split;

	split = NULL;
	if (buf == NULL)
		return (NULL);
	while (buf != NULL)
	{
		if (line == NULL)
			tmp = ft_strdup(buf);
		else
			tmp = ft_strjoin(line, buf, 0);
		if (tmp == NULL)
			return (NULL);
		if (line != NULL)
			free(line);
		line = ft_strdup(tmp);
		free(tmp);
		free(buf);
		if (line == NULL)
			return (NULL);
		buf = get_next_line(fd);
	}
	split = ft_split(line, '\n');
	free(line);
	return (split);
}

// int	get_z(char *line, int i, int *z)
// {
// 	int	temp;

// 	while (line[i] == ' ' && line[i])
// 		i++;
// 	if (!((line[i] == '-' || line[i] == '+' || (line[i] >= '0'
// 					&& line[i] <= '9')) && line[i]))
// 		return (-1);
// 	temp = ft_atoi(&line[i]);
// 	if (temp > *z)
// 		*z = temp;
// 	while ((line[i] == '-' || line[i] == '+') && line[i])
// 		i++;
// 	while (line[i] >= '0' && line[i] <= '9' && line[i])
// 		i++;
// 	while ((line[i] == ',' || line[i] == ' ' || line[i] == '\n') && line[i])
// 		i++;
// 	return (i);
// }

char	**main_2(int argc, char **argv, t_info *info)
{
	int		fd;
	char	**line;
	int		i;
	int		j;
	
	if (argc != 2)
		return (NULL);
	fd = open(argv[1], O_RDONLY);
	line = prep_line(fd, get_next_line(fd), NULL, NULL);
	if (line == NULL)
		return (NULL);
	info->tile_size = 30;
	info->wd_width = 1000;
	info->wd_height = 800;
	info->img.img_ptr = NULL;
	i = 0;
	while (line[i])
	{
		j = 0;
		while (line[i][j])
		{
			if (line[i][j] == 'N' || line[i][j] == 'S' || line[i][j] == 'E' || line[i][j] == 'W')
			{
				info->player.x = j * info->tile_size;
				info->player.y = i * info->tile_size;
				if (line[i][j] == 'N')
				{
					info->player.angle = 3 * PI / 2;
					info->player.dirx = cos(info->player.angle) * 5;
					info->player.diry = sin(info->player.angle) * 5;
				}
				else if (line[i][j] == 'S')
				{
					info->player.angle = PI / 2;
					info->player.dirx = cos(info->player.angle) * 5;
					info->player.diry = sin(info->player.angle) * 5;
				}
				else if (line[i][j] == 'E')
				{
					info->player.angle = 0;
					info->player.dirx = cos(info->player.angle) * 5;
					info->player.diry = sin(info->player.angle) * 5;
				}
				else if (line[i][j] == 'W')
				{
					info->player.angle = PI;
					info->player.dirx = cos(info->player.angle) * 5;
					info->player.diry = sin(info->player.angle) * 5;
				}
				line[i][j] = '0';
			}
			j++;
		}
		i++;
	}
	return (line);
}
