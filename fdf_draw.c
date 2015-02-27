/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vame <vame@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/10 12:51:56 by vame              #+#    #+#             */
/*   Updated: 2015/02/27 16:43:43 by vame             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void				fdf_print_into_img(t_win *env, int x, int y, int color)
{
	int				i;

	if (y >= 0 && x >= 0 && x * 4 + y * env->len < (env->h - 19) * env->len)
	{
		i = x * 4 + y * env->len;
		env->img_str[i] = (color & 0xFF);
		env->img_str[i + 1] = (color & 0xFF00) >> 8;
		env->img_str[i + 2] = (color & 0xFF0000) >> 16;
	}
}

static void			fdf_pxl_proj(t_pixel *pxl, int z, t_win *env)
{
	int					i;
	int					j;
	float				x;
	float				y;
	float				xyz[4];
	float				r[4];

	z = z * env->coef_z;
	xyz[0] = pxl->x;
	xyz[1] = pxl->y;
	xyz[2] = z;
	xyz[3] = 1;
	j = 0;
	while (j++ < 4)
	{
		i = 0;
		r[j - 1] = 0;
		while (i++ < 4)
			r[j - 1] += env->m.main[j - 1][i - 1] * xyz[i - 1];
	}
	x = env->o_x + sqrt(2) / 2 * (r[0] - r[1]);
	y = env->o_y - (sqrt(2) / sqrt(3) * r[2] - (1 / sqrt(6)) * (r[0] + r[1]));
	if (x < env->w - 19)
		fdf_print_into_img(env, x, y, pxl->color);
}

static void			fdf_filling(t_win *env, t_pixel px, int x_pxl, int y_pxl)
{
	float			alti;
	float			diff;
	t_pixel			p;
	t_pixel			d;

	alti = env->map->points[y_pxl][x_pxl];
	p.y = 1;
	p.x = 0;
	while (p.y < env->map->coef && y_pxl + 1 < env->map->y)
	{
		diff = env->map->points[y_pxl][x_pxl] - env->map->points[y_pxl + 1][x_pxl];
		diff /= env->map->coef;
		fdf_index_alti(alti - p.y * diff, env, &d);
		d.color = fdf_color_degrade(d.color_a, d.color_b, d.index);
		d.x = px.x + p.x;
		d.y = px.y + p.y;
		fdf_pxl_proj(&d, alti - p.y * diff, env);
		p.y += 1;
	}
	p.y = 0;
	p.x = 1;
	while (p.x < env->map->coef && x_pxl + 1 < env->map->points[y_pxl][0])
	{
		diff = env->map->points[y_pxl][x_pxl] - env->map->points[y_pxl][x_pxl + 1];
		diff /= env->map->coef;
		fdf_index_alti(alti - p.x * diff, env, &d);
		d.color = fdf_color_degrade(d.color_a, d.color_b, d.index);
		d.x = px.x + p.x;
		d.y = px.y + p.y;
		fdf_pxl_proj(&d, alti - p.x * diff, env);
		p.x += 1;
	}
}

void				fdf_draw(t_win *env)
{
	int				x;
	int				y;
	float			tmps;
	clock_t			t1;
	clock_t			t2;
	t_pixel			pxl;

	y = 0;
	t1 = clock();
	while (y < env->map->y)
	{
		x = 1;
		pxl.y = y * env->map->coef;
		while (x < env->map->points[y][0])
		{
			pxl.x = (x - 1) * env->map->coef;
			fdf_index_alti(env->map->points[y][x], env, &pxl);
			pxl.color = fdf_color_degrade(pxl.color_a, pxl.color_b, pxl.index);
			fdf_pxl_proj(&pxl, env->map->points[y][x], env);
			fdf_filling(env, pxl, x, y);
			x++;
		}
		y++;
	}
	t2 = clock();
	tmps = (float)(t2-t1)/CLOCKS_PER_SEC;
	printf("-- FIN DRAW en %f sec --\n", tmps);
}
