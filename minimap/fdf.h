/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 17:53:26 by user42            #+#    #+#             */
/*   Updated: 2022/01/03 17:53:28 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "mlx_linux/mlx.h"
# include <fcntl.h>
# include <stdlib.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include <math.h>
# include "get_next_line.h"


#include <stdio.h>

#define PI 3.1415926535

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

typedef struct s_img
{
	void	*img_ptr;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}				t_img;

typedef struct	s_player
{
	float x;
	float y;
	float dirx;
	float diry;
	float angle;
}				t_player;

typedef struct s_info
{
	void	*id;
	void	*wd_ptr;
	int		z;
	int		wd_height;
	int		wd_width;
	int		longest_line;
	int		col;
	int		tile_size;
	int		i;
	int		color;
	t_img	img;
	t_player player;
	char **line;
}				t_info;

int		ft_wordcount(char const *str, char c);
int		ft_word_size(char const *str, char c, int i);
void	ft_copy_split(char const *str, char c, int i, char *tab);
char	**ft_split(char const *s, char c);

int		ft_atoi(const char *str);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char const *s1, char const *s2, int i);

//bresenham
void	prep_axe(t_coor *coor, t_bre *bre);
void	correct_axe(t_bre *bre);
void	bresenham_new(t_info *info, t_img *tmp, t_coor *coor);

//utils
void	clear_background(t_info *info, t_img *tmp);
void	set_coor(t_info *info, t_coor *coor);

//render
void	draw_player(t_info *info, t_img *tmp);
void	draw_minimap(t_info *info, t_img *tmp, int x, int y);
int		render(t_info *info);

//prep_wd
char	**prep_line(int fd, char *buf, char *line, char *tmp);
char	**main_2(int argc, char **argv, t_info *info);

//keypress
int		key_release(int key_sym, t_info *info);
void	up_down(t_info *info, int key_sym);
void	left_right(t_info *info, int key_sym);
int		key_press(int key_sym, t_info *info);
int		handle_no_event(void);

//main
void	img_pix_put(t_info *info, t_img *img, int x, int y);
int		destroyer(t_info *info, char **line);
int		destroyer2(t_info *info);
int		main(int argc, char **argv);

#endif
