/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_content.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saich <saich@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 19:44:13 by saich             #+#    #+#             */
/*   Updated: 2022/06/20 20:50:24 by saich            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_info	*init_info(void)
{
	t_info	*info;

	if (check_malloc(&info, sizeof(t_info)))
		return (NULL);
	if (check_malloc(&info->lst, sizeof(t_list)))
		return (NULL);
	info->env.pos_dir = 0;
	ft_bzero(&info->env, sizeof(info->env));
	info->texture.celling = NULL;
	info->texture.ea_path = NULL;
	info->texture.floor = NULL;
	info->map = NULL;
	info->texture.no_path = NULL;
	info->texture.so_path = NULL;
	info->texture.we_path = NULL;
	info->str = NULL;
	return (info);
}

static char	*trim_nl(char *str)
{
	char	*tmp;
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] != '\n')
			len++;
		i++;
	}
	if (check_malloc(&tmp, sizeof(char) * len + 1))
		return (NULL);
	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] != '\n')
			tmp[len++] = str[i];
		i++;
	}
	tmp[len] = '\0';
	free(str);
	return (tmp);
}

static char	*trim_space(char *str)
{
	char	*tmp;
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\n')
			len++;
		i++;
	}
	if (check_malloc(&tmp, sizeof(char) * len + 1))
		return (NULL);
	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\n')
			tmp[len++] = str[i];
		i++;
	}
	tmp[len] = '\0';
	free(str);
	return (tmp);
}

static int	suppress_space(t_list **lst)
{
	t_list	*tmp;

	suppress_emptyl(lst);
	tmp = *lst;
	while (tmp)
	{
		if (!is_map(tmp->content))
			tmp->content = trim_space(tmp->content);
		else
			tmp->content = trim_nl(tmp->content);
		if (!tmp->content)
			return (print_error(strerror(errno)));
		tmp = tmp->next;
	}
	return (0);
}

void	*check_content(t_info *info)
{
	if (suppress_space(info->lst))
		return (NULL);
	if (right_conf_for_cub(info->lst, info))
	{
		print_error("Bad configuration file ! Just bad man\n");
		return (NULL);
	}
	parse_map(info->map, info);
	/* if (check_rgb(info->texture.celling, 1, info->texture) || \
check_rgb(info->texture.celling, 1, info->texture)) */
		return (NULL);
	free_info(info);
	return (NULL);
}

	/* printf("%s\n%s\n%s\n%s\n%s\n%s\n", info->celling, info->ea_path, 
	info->floor, info->no_path, info->so_path, info->we_path);
	for (int i = 0; info->map[i]; i++)
		printf("%s\n", info->map[i]); */
