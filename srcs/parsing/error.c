/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saich <saich@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 18:53:16 by saich             #+#    #+#             */
/*   Updated: 2022/06/20 18:54:38 by saich            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	display_error(char *msg, int code, t_info *info)
{
	if (code != 0)
		printf("Error\n");
	printf("%s\n", msg);
	free_info(info);
	exit(code);
}

void	handle_error(int ret, t_info *info)
{
	if (ret == 10)
		display_error("missing 1 on top of a line", EXIT_FAILURE, info);
	else if (ret == 11)
		display_error("map is not surrounded by 1", EXIT_FAILURE, info);
	else if (ret == 12)
		display_error("space is not surrounded by 1", EXIT_FAILURE, info);
	else if (ret == 13)
		display_error("missing 1 at the end of a line", EXIT_FAILURE, info);
}
