/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saich <saich@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 20:28:43 by saich             #+#    #+#             */
/*   Updated: 2022/07/07 19:49:40 by saich            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_map(char **map)
{
	int		i;

	i = 0;
	if (map)
	{
		while (map[i])
		{
			free(map[i]);
			i++;
		}
		free(map);
	}
}

int	count_lst(t_list *lst)
{
	int		i;
	t_list	*tmp;

	i = 0;
	tmp = lst;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

void	*free_info(t_info *info)
{
	if (info->env.celling)
		free(info->env.celling);
	if (info->env.wall_ea.path)
		free(info->env.wall_ea.path);
	if (info->env.floor)
		free(info->env.floor);
	if (info->env.wall_so.path)
		free(info->env.wall_so.path);
	if (info->env.wall_we.path)
		free(info->env.wall_we.path);
	if (info->env.wall_no.path)
		free(info->env.wall_no.path);
	free_map(info->map);
	ft_lstclear(info->lst, free);
	free(info->lst);
	free(info);
	return (NULL);
}
