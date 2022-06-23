/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_rgb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saich <saich@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 17:21:52 by saich             #+#    #+#             */
/*   Updated: 2022/06/23 21:35:52 by saich            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_rgb(t_texture *texture)
{
	texture->c_rgb[0] = -1;
	texture->c_rgb[1] = -1;
	texture->c_rgb[2] = -1;
	texture->f_rgb[0] = -1;
	texture->f_rgb[1] = -1;
	texture->f_rgb[2] = -1;
}

static int	check_int(t_texture *texture)
{
	int	i;

	i = 0;
	while (texture->c_rgb[i])
	{
		if (texture->c_rgb[i] < 0 || texture->c_rgb[i] > 255)
			return (1);
		i++;
	}
	i = 0;
	while (texture->f_rgb[i])
	{
		if (texture->f_rgb[i] < 0 || texture->f_rgb[i] > 255)
			return (1);
		i++;
	}
	return (0);
}

int	check_rgb(char *str, int type, t_texture *texture)
{
	int		i;
	int		start;
	int		count;
	char	*tmp;

	i = 0;
	count = 0;
	start = 0;
	if (ft_strlen(str) > 10)
		return (1);
	while (count < 3)
	{
		while (str[i] && ft_isdigit(str[i]))
			i++;
		if (str[i] != '\0' && str[i] != ',')
			return (1);
		if (check_malloc(&tmp, sizeof(char) * i + 1))
			return (1);
		ft_strncpy(tmp, str + start, i);
		start = i + 1;
		i = start;
		if (type)
		{
			if (texture->c_rgb[0] == -1)
			{
				count++;
				texture->c_rgb[0] = ft_atoi(tmp);
			}
			else if (texture->c_rgb[1] == -1)
			{
				count++;
				texture->c_rgb[1] = ft_atoi(tmp);
			}
			else if (texture->c_rgb[2] == -1)
			{
				count++;
				texture->c_rgb[2] = ft_atoi(tmp);
			}
		}
		else
		{
			if (texture->f_rgb[0] == -1)
			{
				count++;
				texture->f_rgb[0] = ft_atoi(tmp);
			}
			else if (texture->f_rgb[1] == -1)
			{
				count++;
				texture->f_rgb[1] = ft_atoi(tmp);
			}
			else if (texture->f_rgb[2] == -1)
			{
				count++;
				texture->f_rgb[2] = ft_atoi(tmp);
			}
			if (count < 3 && !str[i - 1])
				return (1);
		}
		free(tmp);
	}
	if (check_int(texture))
		return (1);
	printf("c_rgb:%i,%i,%i , f_rgb:%i,%i,%i\n", texture->c_rgb[0], texture->c_rgb[1], texture->c_rgb[2], texture->f_rgb[0], texture->f_rgb[1], texture->f_rgb[2]);
	return (0);
}
