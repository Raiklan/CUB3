/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_rgb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saich <saich@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 17:21:52 by saich             #+#    #+#             */
/*   Updated: 2022/07/06 19:39:10 by saich            ###   ########.fr       */
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

static int	check_int255(t_texture *texture)
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

static int	get_rgb_floor(t_texture *texture, char *str)
{
	int		i;
	char	*tmp;
	int		start;
	int		j;

	i = 0;
	j = 0;
	start = 0;
	while (str[i])
	{
		while (str[i] && ft_isdigit(str[i]))
			i++;
		if (str[i] != '\0' && str[i] != ',')
			return (1);
		if (check_malloc(&tmp, sizeof(char) * i + 1))
			return (1);
		ft_strncpy(tmp, str + start, i - start);
		texture->f_rgb[j] = ft_atoi(tmp);
		start = i + 1;
		i = start;
		j++;
		free(tmp);
	}
	return (0);
}

static int	get_rgb_ceil(t_texture *texture, char *str)
{
	int		i;
	char	*tmp;
	int		start;
	int		j;

	i = 0;
	j = 0;
	start = 0;
	while (str[i])
	{
		while (str[i] && ft_isdigit(str[i]))
			i++;
		if (str[i] != '\0' && str[i] != ',')
			return (1);
		if (check_malloc(&tmp, sizeof(char) * i + 1))
			return (1);
		ft_strncpy(tmp, str + start, i);
		texture->c_rgb[j] = ft_atoi(tmp);
		start = i + 1;
		i = start;
		j++;
		free(tmp);
	}
	return (0);
}

int	check_rgb(char *str_c, char *str_f, t_texture *texture)
{
	if (ft_strlen(str_c) > 11 || ft_strlen(str_f) > 11)
		return (1);
	if (get_rgb_floor(texture, str_f) || get_rgb_ceil(texture, str_c))
		return (1);
	if (check_int255(texture))
		return (1);
	return (0);
}
