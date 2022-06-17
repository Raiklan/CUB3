/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_rgb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saich <saich@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 17:21:52 by saich             #+#    #+#             */
/*   Updated: 2022/06/17 17:27:16 by saich            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"



int	check_rgb(char *str)
{
	int		i;
	int		virg;
	char	*tmp;

	i = 0;
	while (str[i] && str[i] != ',')
		i++;
	virg = i;
	i = 0;
	while (i < virg)
		tmp[i++] = str[i];
	tmp[i] = '\0';
	i = ft_atoi(tmp);
	if (i > 255 || i < 0)
		return (1);
}
