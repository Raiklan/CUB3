/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saich <saich@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 16:39:47 by saich             #+#    #+#             */
/*   Updated: 2022/07/19 16:36:03 by saich            ###   ########.fr       */
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

# define ROTATESPEED 0.01
# define MOVESPEED 0.01

typedef struct s_cast
{
	float		posx;
	float		posy;
	float		dirx;
	float		diry;
	float		planx;
	float		plany;
	float		camerax;
	float		ray_dirx;
	float		ray_diry;
	float		wall_hit;
	float		side_distx;
	float		side_disty;
	float		delta_distx;
	float		delta_disty;
	float		perpwalldist;
	int			**buffer;
	int			screenh;
	int			screenw;
	int			mapx;
	int			mapy;
	int			stepx;
	int			stepy;
	int			hit;
	int			side;
	int			line_height;
	int			draw_start;
	int			draw_end;
	int			x_event;
	int			x_mask;
	int			color;
}	t_cast;

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

typedef struct s_key
{
	int	w;
	int	s;
	int	a;
	int	d;
	int	left;
	int	right;
}				t_key;

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

typedef struct s_minimap
{
	int	i;
	int	j;
	int	pixel_count;
	int	col_count;
	int	x;
	int	y;
	int	tile_size;
}				t_minimap;

typedef struct s_bre
{
	int		width;
	int		height;
	int		dx1;
	int		dy1;
	int		dx2;
	int		dy2;
	int		longest;
	int		shortest;
	int		numerator;
}				t_bre;

typedef struct s_coor
{
	int		x1;
	int		y1;
	int		xold;
	int		yold;
	int		tile_size;
}				t_coor;

typedef struct s_info
{
	t_list			**lst;
	t_env			env;
	t_mlx			mlx;
	t_resolution	resolution;
	t_cast			cast;
	t_key			key;
	char			**map;
	int				minimap_color;
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
int		leave_prog(void *info);


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
int		check_island(char **map);
int		exit_window(t_info *info, char *msg);
int		size_map(char **map);

//check_rgb.c
int		check_rgb(char *str_c, char *str_f, t_texture *text);
void	init_rgb(t_texture *texture);
int		parse_color(t_info *info, char *line, int ret);
int		get_color(int r, int g, int b, t_info *info);

//texture.c
void	get_all_texture(t_info	*info);
void	get_texture(t_texture *tex, t_info *info);

//raycasting.c
int		raycasting(t_info *info);
void	find_wall(t_info	*info);
void	build_wall(t_info *info);
void	build_ray(t_info *info);
void	init_raycast(t_info *info, int x);

//rotate.c
void	rotate_left(t_info *info);
void	rotate_right(t_info *info);

//key.c
int	get_number(int key, t_info *info);
int	push_nbr(int key, t_info *info);

//movement.c
void	ft_move(t_info *info);
void	move_back(float dirx, float diry, t_info *info);
void	move_front(float dirx, float diry, t_info *info);
void	move_left(float dirx, float diry, t_info *info);
void	move_right(float dirx, float diry, t_info *info);

//draw.c
void	set_wall_hit(t_info *info);
void	build_t(t_info *info, t_texture *tex, int i);
void	draw_wall(t_info *info, int x);
void	draw_background(t_info *info, int i);

//minimap.c
void	draw_player_rays(t_info *info, t_minimap *minimap);
void	draw_player(t_info *info, t_minimap *minimap);
t_minimap	minimap_init(void);
void	chose_minimap_color(t_info *info, t_minimap *minimap);
void	draw_minimap(t_info *info, t_minimap minimap);

//bresenham.c
void	img_pix_put(t_info *info, int x, int y);
void	prep_axe(t_coor *coor, t_bre *bre);
void	correct_axe(t_bre *bre);
void	bresenham_new(t_info *info, t_coor *coor);

#endif
