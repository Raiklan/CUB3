/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saich <saich@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 18:04:24 by gpaul             #+#    #+#             */
/*   Updated: 2022/06/09 17:05:38 by saich            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list		*cpy;
	int			size;

	size = ft_lstsize(*lst);
	cpy = *lst;
	if (*lst)
	{
		while (0 < size)
		{
			cpy = (*lst)->next;
			(*del)((*lst)->content);
			free(*lst);
			*lst = cpy;
			size--;
		}
	}
	(*lst) = NULL;
}
