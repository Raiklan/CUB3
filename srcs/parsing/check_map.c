/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saich <saich@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 23:55:38 by saich             #+#    #+#             */
/*   Updated: 2022/06/10 16:45:14 by saich            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	right_name(char *str, t_info *info)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	if (!ft_strncmp(str, "NO", 2))
	{
		info->no_path = ft_substr(str, 2, ft_strlen(str));
		if (!info->no_path)
			return (-1);
		flag = 1;
	}
	if (ft_strlen(str) > 2 && str[i] == 'S' && str[i + 1] == 'O')
	{
		info->so_path = ft_substr(str, 2, ft_strlen(str));
		if (!info->so_path)
			return (-1);
		flag = 1;
	}
	if (ft_strlen(str) > 2 && str[i] == 'W' && str[i + 1] == 'E')
	{
		info->we_path = ft_substr(str, 2, ft_strlen(str));
		flag = 1;
		if (!info->we_path)
			return (-1);
	}
	if (ft_strlen(str) > 2 && str[i] == 'E' && str[i + 1] == 'A')
	{
		info->ea_path = ft_substr(str, 2, ft_strlen(str));
		flag = 1;
		if (!info->ea_path)
			return (-1);
	}
	if (ft_strlen(str) > 2 && str[i] == 'F' && ft_isdigit(str[i + 1]))
	{
		info->floor = ft_substr(str, 1, ft_strlen(str));
		flag = 1;
		if (!info->floor)
			return (-1);
	}
	if (ft_strlen(str) > 2 && str[i] == 'C' && ft_isdigit(str[i + 1]))
	{
		info->celling = ft_substr(str, 1, ft_strlen(str));
		flag = 1;
		if (!info->celling)
			return (-1);
	}
	if (flag)
		return (1);
	return (0);
}
static int	cpy_map(int count, t_info *info, t_list *lst)
{
	int		i;
	t_list	*tmp;
	
	i = 0;
	tmp = lst;
	if (count == 6)
	{
		if (check_malloc(&(info->map), sizeof(char *) * count_lst(tmp) + 1))
			return (print_error("Malloc failed in copying map content\n"));
		while (tmp)
		{
			if (check_malloc(&(info->map[i]), ft_strlen(tmp->content) + 1))
				return (print_error("Malloc failed in copying map content\n"));
			ft_strcpy(info->map[i++], tmp->content);
			tmp = tmp->next;
		}
		info->map[i] = NULL;
	}
	return (0);
}
int	right_conf_for_cub(t_list **lst, t_info *info)
{
	t_list	*tmp;
	int		count;
	int		ret;

	count = 0;
	tmp = *lst;
	while (tmp)
	{
		ret = right_name(tmp->content, info);
		if (ret == -1)
			return (print_error("Malloc failed in ft_substr \
to get data from .cub\n"));
		if (ret)
			count++;
		if (is_map(tmp->content))
		{
			if (cpy_map(count, info, tmp))
				return (EXIT_FAILURE);
			break ;
		}
		tmp = tmp->next;
	}
	if (count != 6)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	is_map(char *str)
{
	int		i;

	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (str[i] && str[i] == '1')
		return (1);
	return (0);
}

int	check_map(t_info *info)
{
	int	i;
	int	j;

	i = 0;
	if (check_border_horiz(info->map[0]))
		return (print_error("Top border of the map is not made of '1' and spaces\n")); // error
	while(info->map[i])
	{
		j = 0;
		if (check_first_wall(info->map[i]))
			return (print_error("Map is not bounded by walls\n"));
		while (info->map[i][j])
		{
			if (info->map[i][j] != '1' && info->map[i][j] != '0' && info->map[i][j] != 'N' \
&& info->map[i][j] != 'S' && info->map[i][j] != 'W' && info->map[i][j] != 'E' && info->map[i][j] != ' ')
				return (print_error("Character of the map can only be : 1, 0, N, E, S, W or spaces\n"));
			j++;
		}
		if (check_last_wall(info->map[i], j - 1))
			return (print_error("Map is not bounded by walls\n"));
		i++;
	}
	if (check_border_horiz(info->map[i - 1]))
		return (print_error("Bottom border of the map is not made of '1' and spaces\n"));
	return (0);
}
