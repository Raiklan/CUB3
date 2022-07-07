/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saich <saich@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 16:39:47 by saich             #+#    #+#             */
/*   Updated: 2022/07/07 19:50:52 by saich            ###   ########.fr       */
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
# include <math.h>
# include "../mlx_linux/mlx.h"
# include "../mlx_linux/mlx_int.h"

typedef struct s_resolution
{
	int	x;
	int	y;
}				t_resolution;

typedef struct s_texture
{
	char			*path;
	int				h;
	int				w;
	unsigned int	*tex_addr;
	void			*tex_ptr;
	int				size_line;
	int				bpp;
	int				endian;
}				t_texture;

typedef struct s_env
{
	char		pos_dir;
	int			pos_coor[2];
	t_texture	wall_we;
	t_texture	wall_ea;
	t_texture	wall_so;
	t_texture	wall_no;
	char		*celling;
	char		*floor;
	int			color_ceil;
	int			color_floor;
}				t_env;

typedef struct s_mlx
{
	void			*mlx_window;
	void			*mlx_ptr;
	void			*img_ptr;
	unsigned int	*img_addr;
	void			*win_ptr;
	int				bpp;
	int				size_line;
	int				endian;
}	t_mlx;

typedef struct s_info
{
	t_list			**lst;
	t_env			env;
	t_mlx			mlx;
	t_resolution	resolution;
	char			**map;
}					t_info;

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

//check_rgb.c
int		check_rgb(char *str_c, char *str_f, t_texture *text);
void	init_rgb(t_texture *texture);
int		parse_color(t_info *info, char *line, int ret);
int		get_color(int r, int g, int b, t_info *info);

#endif
