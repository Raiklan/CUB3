/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_content.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saich <saich@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 19:44:13 by saich             #+#    #+#             */
/*   Updated: 2022/06/10 16:44:04 by saich            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_info	*init_info(void)
{
	t_info	*info;

	if (check_malloc(&info, sizeof(t_info)))
		return (NULL);
	info->celling = NULL;
	info->ea_path = NULL;
	info->floor = NULL;
	info->map = NULL;
	info->no_path = NULL;
	info->so_path = NULL;
	info->we_path = NULL;
	info->str = NULL;
	info->next = NULL;
	return (info);
}

static char	*trim_nl(char *str)
{
	char	*tmp;
	int		i;
	int		len;

	if (check_malloc(&tmp, sizeof(char) * ft_strlen(str) + 1))
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

t_info	*check_content(t_list **lst)
{
	t_info	*info;
	t_list	*tmp;

	info = init_info();
	if (!info)
		return (NULL);
	if (suppress_space(lst))
		return (NULL);
	if (right_conf_for_cub(lst, info))
	{
		print_error("Missing an element for configuration or map isn't \
the last element\n");
		return (NULL);
	}
	for (int i = 0; info->map[i]; i++)
		printf("%s\n", info->map[i]);
	if (check_map(info))
		return (NULL);
	tmp = *lst;
	while (tmp)
	{
		printf("%s\n", tmp->content);
		tmp = tmp->next;
	}
	printf("%s\n%s\n%s\n%s\n%s\n%s\n", info->celling, info->ea_path, info->floor, info->no_path, info->so_path, info->we_path);
	for (int i = 0; info->map[i]; i++)
		printf("%s\n", info->map[i]);
	ft_lstclear(lst, free);
	free_info(info);
	return (NULL);
}
