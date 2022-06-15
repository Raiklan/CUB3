/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saich <saich@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 23:55:38 by saich             #+#    #+#             */
/*   Updated: 2022/06/15 18:12:22 by saich            ###   ########.fr       */
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
	if (!ft_strncmp(str, "SO", 2))
	{
		info->so_path = ft_substr(str, 2, ft_strlen(str));
		if (!info->so_path)
			return (-1);
		flag = 1;
	}
	if (!ft_strncmp(str, "WE", 2))
	{
		info->we_path = ft_substr(str, 2, ft_strlen(str));
		flag = 1;
		if (!info->we_path)
			return (-1);
	}
	if (!ft_strncmp(str, "EA", 2))
	{
		info->ea_path = ft_substr(str, 2, ft_strlen(str));
		flag = 1;
		if (!info->ea_path)
			return (-1);
	}
	if (!ft_strncmp(str, "F", 1) && str[i + 1] &&ft_isdigit(str[i + 1]))
	{
		info->floor = ft_substr(str, 1, ft_strlen(str));
		flag = 1;
		if (!info->floor)
			return (-1);
	}
	if (!ft_strncmp(str, "C", 1) && str[i + 1] && ft_isdigit(str[i + 1]))
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
			ret = 2;
			if (cpy_map(count, info, tmp))
				return (EXIT_FAILURE);
			break ;
		}
		tmp = tmp->next;
	}
	if (count != 6 || ret != 2)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

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
