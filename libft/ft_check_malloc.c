/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_malloc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaul <gpaul@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 15:49:26 by gpaul             #+#    #+#             */
/*   Updated: 2021/12/14 15:49:28 by gpaul            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	check_malloc(void *dest, size_t size)
{
	*(void **) dest = malloc(size);
	if (*(void **) dest == NULL)
		return (1);
	memset(*(void **) dest, 0, size);
	return (0);
}
