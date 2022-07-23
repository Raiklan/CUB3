/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saich <saich@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 23:55:38 by saich             #+#    #+#             */
/*   Updated: 2022/07/23 15:52:12 by saich            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	right_name3(char *str, t_info *info)
{
	if (!ft_strncmp(str, "WE", 2) && !info->env.wall_we.path)
	{
		info->env.wall_we.path = ft_substr(str, 2, ft_strlen(str));
		if (!info->env.wall_we.path)
			return (-1);
		return (1);
	}
	if (!ft_strncmp(str, "C", 1) && str[1] && ft_isdigit(str[1])
		&& !info->env.celling)
	{
		info->env.celling = ft_substr(str, 1, ft_strlen(str));
		if (!info->env.celling)
			return (-1);
		return (1);
	}
	return (0);
}

static int	right_name2(char *str, t_info *info)
{
	int	ret;

	ret = 0;
	if (!ft_strncmp(str, "EA", 2) && !info->env.wall_ea.path)
	{
		info->env.wall_ea.path = ft_substr(str, 2, ft_strlen(str));
		ret = 1;
		if (!info->env.wall_ea.path)
			return (-1);
	}
	if (!ft_strncmp(str, "F", 1) && str[1] && ft_isdigit(str[1])
		&& !info->env.floor)
	{
		info->env.floor = ft_substr(str, 1, ft_strlen(str));
		ret = 1;
		if (!info->env.floor)
			return (-1);
	}
	if (!ret)
		ret = right_name3(str, info);
	return (ret);
}

static int	right_name(char *str, t_info *info, int flag)
{
	flag = 0;
	if (!ft_strncmp(str, "NO", 2) && !info->env.wall_no.path)
	{
		info->env.wall_no.path = ft_substr(str, 2, ft_strlen(str));
		if (!info->env.wall_no.path)
			return (-1);
		flag = 1;
	}
	if (!ft_strncmp(str, "SO", 2) && !info->env.wall_so.path)
	{
		info->env.wall_so.path = ft_substr(str, 2, ft_strlen(str));
		if (!info->env.wall_so.path)
			return (-1);
		flag = 1;
	}
	if (flag)
		return (1);
	flag = right_name2(str, info);
	return (flag);
}

static int	cpy_map(int count, t_info *info, t_list *lst)
{
	int		i;
	t_list	*tmp;

	i = 0;
	tmp = lst;
	if (count == 6)
	{
		if (check_malloc(&(info->map), sizeof(char *) * (count_lst(tmp) + 1)))
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
		ret = right_name(tmp->content, info, ret);
		if ((!ret && !is_map(tmp->content)) || ret == -1)
			return (1);
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
