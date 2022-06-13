/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_border.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saich <saich@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 16:19:22 by saich             #+#    #+#             */
/*   Updated: 2022/06/13 20:04:39 by saich            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_border_horiz(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '1' || line[i] == ' ')
			i++;
		else
			return (1);
	}
	return (0);
}

int	check_first_wall(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (line[i] != '1')
		return (1);
	return (0);
}

int	check_last_wall(char *line, int i)
{
	while (i >= 0 && line[i] == ' ')
		i--;
	if (line[i] != '1')
		return (1);
	return (0);
}
