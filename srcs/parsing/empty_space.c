/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   empty_space.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saich <saich@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 22:48:24 by saich             #+#    #+#             */
/*   Updated: 2022/06/20 19:26:28 by saich            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_map(char *str)
{
	int		i;

	i = 0;
	while (str[i] && (str[i] == ' '))
		i++;
	if (str[i] && str[i] == '1')
		return (1);
	return (0);
}

int	map_length(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i - 1);
}

void	get_pos(char **map, t_info *info)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E'
				|| map[i][j] == 'W')
			{
				if (info->env.pos_dir == 0)
				{
					info->env.pos_dir = map[i][j];
					info->env.pos_coor[0] = i;
					info->env.pos_coor[1] = j;
				}
				else if (info->env.pos_dir != 0)
					display_error("position already set", EXIT_FAILURE, info);
			}
			j++;
		}
		i++;
	}
}

int	empty_space_line(t_list *lst)
{
	char	*str;
	int		i;
	int		count;

	i = 0;
	count = 0;
	str = lst->content;
	while (str[i])
	{
		if (str[i] != '\n' && str[i] != ' ' && str[i] != '\t')
			count = 1;
		i++;
	}
	if (count)
		return (0);
	return (1);
}

void	suppress_emptyl(t_list **lst)
{
	t_list	*cur;
	t_list	*tmp;

	while (*lst && empty_space_line(*lst))
	{
		cur = *lst;
		*lst = (*lst)->next;
		free(cur->content);
		free(cur);
	}
	tmp = *lst;
	while (tmp)
	{
		cur = tmp->next;
		while (cur && empty_space_line(cur))
		{
			tmp->next = NULL;
			if (cur->next)
				tmp->next = cur->next;
			free(cur->content);
			free(cur);
			cur = tmp->next;
		}
		tmp = tmp->next;
	}
}
