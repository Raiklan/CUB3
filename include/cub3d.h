/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saich <saich@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 16:39:47 by saich             #+#    #+#             */
/*   Updated: 2022/06/13 20:18:32 by saich            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include "get_next_line.h"
# include <string.h>
# include <errno.h>

typedef struct s_info
{
	t_list			**lst;
	char			*str;
	char			*no_path;
	char			*so_path;
	char			*we_path;
	char			*ea_path;
	char			*floor;
	char			*celling;
	char			**map;
	struct s_info	*next;
}				t_info;

			/* Parsing of the .cub file */
int		print_error(char *str);
void	*check_content(t_info *info);
int		empty_space_line(t_list *lst);
void	suppress_emptyl(t_list **lst);
int		right_conf_for_cub(t_list **lst, t_info *info);
int		is_map(char *str);
int		check_map(t_info *info);
int		check_border_horiz(char *line);
int		check_first_wall(char *line);
int		check_last_wall(char *line, int i);
t_info	*init_info(void);

//free_utils.c
void	free_info(t_info *info);
int		count_lst(t_list *lst);
#endif
