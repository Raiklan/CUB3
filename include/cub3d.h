/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saich <saich@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 16:39:47 by saich             #+#    #+#             */
/*   Updated: 2022/07/06 19:29:24 by saich            ###   ########.fr       */
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

typedef struct	s_env
{
	char		pos_dir;
	int			pos_coor[2];
}				t_env;

typedef struct	s_texture
{
	int			f_rgb[3];
	int			c_rgb[3];
	char		*no_path;
	char		*so_path;
	char		*we_path;
	char		*ea_path;
	char		*floor;
	char		*celling;
}				t_texture;

typedef struct	s_info
{
	t_list		**lst;
	t_env		env;
	t_texture	*texture;
	char		*str;
	char		**map;
}				t_info;

			/* Parsing of the .cub file */
int		print_error(char *str);
void	*check_content(t_info *info);
int		empty_space_line(t_list *lst);
void	suppress_emptyl(t_list **lst);
void	get_pos(char **map, t_info *info);
int		right_conf_for_cub(t_list **lst, t_info *info);
int		is_map(char *str);
int		check_map(t_info *info);
int		check_border_horiz(char *line);
int		check_first_wall(char *line);
int		check_last_wall(char *line, int i);
t_info	*init_info(void);

//free_utils.c
void	*free_info(t_info *info);
int		count_lst(t_list *lst);

//check_spaces.c
int		check_space(char **map, int i, int j);
int		check_space_closed(char **map, int i, int j, int limit);
int		check_closed(char **map, int i, int j, int last);
int		map_length(char **map);

//check_limit.c
void	parse_map(char **map, t_info *info);

//error.c
void	handle_error(int ret, t_info *info);
void	*display_error(char *msg, int code, t_info *info);

//check_rgc.c
int		check_rgb(char *str_c, char *str_f, t_texture *text);
void	init_rgb(t_texture *texture);
#endif
