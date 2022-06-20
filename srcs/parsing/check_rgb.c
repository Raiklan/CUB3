/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_rgb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saich <saich@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 17:21:52 by saich             #+#    #+#             */
/*   Updated: 2022/06/20 20:49:52 by saich            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_rgb(t_texture text)
{
	text.c_rgb[0] = -1;
	text.c_rgb[1] = -1;
	text.c_rgb[2] = -1;
	text.f_rgb[0] = -1;
	text.f_rgb[1] = -1;
	text.f_rgb[2] = -1;
}

static int	filled_type(int type, t_texture text)
{
	if (type)
	{
		if (text.c_rgb[0] != -1 && text.c_rgb[1] != -1 && text.c_rgb[2] != -1)
			return (1);
		return (0);
	}
	else
	{
		if (text.f_rgb[0] != -1 && text.f_rgb[1] != -1 && text.f_rgb[2] != -1)
			return (1);
		return (0);
	}
}

int	check_rgb(char *str, int type, t_texture text)
{
	int		i;
	int		start;
	char	*tmp;

	i = 0;
	start = 0;
	init_rgb(text);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
		{
			if (str[i] == ',')
			{
				tmp = ft_strncpy(tmp, str + start, i);
				start = i + 1;
				if (type)
				{
					if (text.c_rgb[0] == -1)
						text.c_rgb[0] = ft_atoi(tmp);
					else if (text.c_rgb[1] == -1)
						text.c_rgb[1] = ft_atoi(tmp);
					else if (text.c_rgb[2] == -1)
						text.c_rgb[2] = ft_atoi(tmp);
				}
				else
				{
					if (text.f_rgb[0] == -1)
						text.f_rgb[0] = ft_atoi(tmp);
					else if (text.f_rgb[1] == -1)
						text.f_rgb[1] = ft_atoi(tmp);
					else if (text.f_rgb[2] == -1)
						text.f_rgb[2] = ft_atoi(tmp);
				}
			}
			else
			{
				printf("c_rgb:%i,%i,%i , f_rgb:%i,%i,%i\n", text.c_rgb[0], text.c_rgb[1], text.c_rgb[2], text.f_rgb[0], text.f_rgb[1], text.f_rgb[2]);
				return (1);
			}
		}
		i++;
	}
	printf("c_rgb:%i,%i,%i , f_rgb:%i,%i,%i\n", text.c_rgb[0], text.c_rgb[1], text.c_rgb[2], text.f_rgb[0], text.f_rgb[1], text.f_rgb[2]);
	return (0);
}
