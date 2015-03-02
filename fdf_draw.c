/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vame <vame@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/10 12:51:56 by vame              #+#    #+#             */
/*   Updated: 2015/03/02 14:16:30 by vame             ###   ########.fr       */
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

void				fdf_pxl_proj(t_pixel *p, int z, t_win *e)
{
	int				i;
	int				j;
	float			xyz[4];
	float			r[4];

	z = z * e->coef_z;
	xyz[0] = p->x;
	xyz[1] = p->y;
	xyz[2] = z;
	xyz[3] = 1;
	j = 0;
	while (j++ < 4)
	{
		i = 0;
		r[j - 1] = 0;
		while (i++ < 4)
			r[j - 1] += e->m.main[j - 1][i - 1] * xyz[i - 1];
	}
	p->x = e->o_x + sqrt(2) / 2 * (r[0] - r[1]);
	p->y = e->o_y - (sqrt(2) / sqrt(3) * r[2] - (1 / sqrt(6)) * (r[0] + r[1]));
	if (p->x < e->w - 19)
		fdf_print_into_img(e, p->x, p->y, p->color);
}

void				fdf_draw(t_win *e)
{
	int				x;
	int				y;
	t_pixel			pxl;

	y = 0;
	while (y < e->map->y)
	{
		x = 1;
		while (x < e->map->points[y][0])
		{
			pxl.y = y * e->map->coef - (e->map->y * e->map->coef) / 2;
			pxl.x = (x - 1) * e->map->coef - e->map->x * e->map->coef / 2;
			fdf_index_alti(e->map->points[y][x], e, &pxl);
			pxl.color = fdf_color_degrade(pxl.color_a, pxl.color_b, pxl.index);
			fdf_pxl_proj(&pxl, e->map->points[y][x], e);
			if (pxl.x > -e->map->coef && pxl.x < e->w - 18 + e->map->coef
				&& pxl.y > -e->map->coef && pxl.y < e->h - 18 + e->map->coef)
				fdf_filling(e, pxl, x, y);
			x++;
		}
		y++;
	}
}
