/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   empty_space.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saich <saich@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 22:48:24 by saich             #+#    #+#             */
/*   Updated: 2022/05/25 23:48:22 by saich            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
