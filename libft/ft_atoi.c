/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saich <saich@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 15:33:12 by gpaul             #+#    #+#             */
/*   Updated: 2022/07/21 17:10:27 by saich            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long int	ft_atoi(char *str)
{
	int				i;
	int				sign;
	long long int	re;

	re = 0;
	i = 0;
	sign = 0;
	while (str[i] && ((str[i] >= 9 && str[i] <= 13) || str[i] == ' '))
		i++;
	if (str[i] && (str[i] == '-' || str[i] == '+'))
	{
		if (str[i] && str[i] == '-')
			sign++;
		i++;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
		re = re * 10 + (str[i++] - '0');
	if (sign == 1)
		return (-re);
	else
		return (re);
}
