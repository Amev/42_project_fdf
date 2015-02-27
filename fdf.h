/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vame <vame@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/09 13:23:42 by vame              #+#    #+#             */
/*   Updated: 2015/02/27 16:53:52 by vame             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft/libft_ext.h"
# include <mlx.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <time.h>
# include <stdio.h>

# define ERR_ARG 1
# define ERR_MAP 2
# define ERR_MAL 3
# define ERR_OPN 4
# define ERR_RED 5
# define ERR_CLS 6
# define ERR_GNL 7

# define KEYCODE_1 49
# define KEYCODE_2 50
# define KEYCODE_3 51

# define PI 3.141592

/*
** structure map
*/

typedef struct		s_map
{
	int				**points;
	int				y;
	int				x;
	int				z_min;
	int				z_max;
	int				coef;
}					t_map;

/*
** structure color
*/

typedef struct		s_color
{
	int				color1;
	int				color2;
	int				color3;
	int				color4;
	int				color5;
	int				color6;
	int				color7;
}					t_color;

/*
** structure matrix
*/

typedef struct		s_matrix
{
	float			**main;
	float			**m_t;
	float			tx;
	float			ty;
	float			tz;
	float			**m_rx;
	float			ax;
	float			**m_ry;
	float			ay;
	float			**m_rz;
	float			az;
	float			**m_s;
	float			sx;
	float			sy;
	float			sz;
}					t_matrix;

/*
** structure mlx
*/

typedef struct		s_win
{
	int				w;
	int				h;
	int				o_x;
	int				o_y;
	float			coef_z;
	void			*mlx;
	void			*win;
	void			*img;
	char			*img_str;
	int				bpp;
	int				len;
	int				endian;
	struct s_map	*map;
	struct s_color	color;
	struct s_matrix	m;
}					t_win;

/*
** structure pixel
*/

typedef struct		s_pixel
{
	float			x;
	float			y;
	float			z;
	int				color;
	int				color_a;
	int				color_b;
	float			index;
}					t_pixel;

/*
** fonctions de creation de la map
*/

void				fdf_create_map(t_map *map, int av, char **ac);
void				fdf_malloc_y_map(t_map *map, char **read);
void				fdf_malloc_x_map(t_map *map, char **split, int y);
char				**fdf_join_line(char **line, char ***read);
char				**fdf_read_map(char *ac);

/*
** fonctions utilitaires du fdf
*/

void				fdf_print_error(int err);

/*
** fonctions de gestion des keyhook
*/

int					key_hook(int keycode, t_win *env);

/*
** fonctions de gestion des keyhook
*/

int					fdf_expose_hook(t_win *env);
void				fdf_key_transform(t_win *env, int keycode);
void				fdf_key_change_coef_z(t_win *env, int keycode);
void				fdf_set_color(int keycode, t_win *env);

/*
** fonctions de dessin
*/

void				fdf_draw(t_win *env);
void				fdf_print_into_img(t_win *env, int x, int y, int color);

/*
** fonctions de gestion de la fenetre
*/

void				fdf_calc_win_param(t_win *e);

/*
** fonctions de gestion des couleurs
*/

int					fdf_color_degrade(int clr_a, int clr_b, int index);

/*
** fonctions de gestion des index d'altitude
*/

int					fdf_create_alti(char *split, t_map *map);
void				fdf_index_alti(float alti, t_win *env, t_pixel *pxl);

/*
** fonctions de gestion des projection et transformation matricielles
*/

void				fdf_matrix_init(t_win *env);
void				fdf_matrix_bzero(t_win *env);
float				**fdf_create_mat(int x, int y);
void				fdf_del_mat(int x, float ***mat);

#endif
