/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saich <saich@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 20:28:43 by saich             #+#    #+#             */
/*   Updated: 2022/06/23 19:22:26 by saich            ###   ########.fr       */
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
	if (info->texture->celling)
		free(info->texture->celling);
	if (info->texture->ea_path)
		free(info->texture->ea_path);
	if (info->texture->floor)
		free(info->texture->floor);
	if (info->texture->no_path)
		free(info->texture->no_path);
	if (info->texture->so_path)
		free(info->texture->so_path);
	if (info->texture->we_path)
		free(info->texture->we_path);
	free(info->texture);
	free_map(info->map);
	ft_lstclear(info->lst, free);
	free(info->lst);
	free(info);
	return (NULL);
}
