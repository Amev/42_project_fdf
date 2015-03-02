/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_filling.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vame <vame@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/02 09:40:02 by vame              #+#    #+#             */
/*   Updated: 2015/03/02 14:16:31 by vame             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
**	Algorithme de Bresenham
**	s[0] = i;
**	s[1] = w;
**	s[2] = h;
**	s[3] = dx1;
**	s[4] = dy1;
**	s[5] = dx2;
**	s[6] = dy2;
**	s[7] = long;
**	s[8] = short;
**	s[9] = error;
*/

static void			fdf_draw_segment(t_pixel p, t_pixel n, t_win *env)
{
	float			dz;
	int				s[10];

	s[0] = 0;
	s[1] = (n.x - p.x);
	s[2] = (n.y - p.y);
	s[3] = s[1] == 0 ? 0 : s[1] / ft_abs(s[1]);
	s[4] = s[2] == 0 ? 0 : s[2] / ft_abs(s[2]);
	s[5] = ft_abs(s[1]) >= ft_abs(s[2]) ? s[3] : 0;
	s[6] = ft_abs(s[1]) >= ft_abs(s[2]) ? 0 : s[4];
	s[7] = ft_abs(s[1]) >= ft_abs(s[2]) ? ft_abs(s[1]) : ft_abs(s[2]);
	s[8] = ft_abs(s[1]) >= ft_abs(s[2]) ? ft_abs(s[2]) : ft_abs(s[1]);
	s[9] = s[7] >> 1;
	dz = (n.z - p.z) / s[7];
	while (s[0]++ < s[7])
	{
		s[9] += s[8];
		p.x += s[9] < s[7] ? s[5] : s[3];
		p.y += s[9] < s[7] ? s[6] : s[4];
		s[9] -= s[9] < s[7] ? 0 : s[7];
		fdf_index_alti(p.z + s[0] * dz, env, &p);
		p.color = fdf_color_degrade(p.color_a, p.color_b, p.index);
		if (p.x < env->w - 19)
			fdf_print_into_img(env, p.x, p.y, p.color);
	}
}

void				fdf_filling(t_win *env, t_pixel p, int x, int y)
{
	t_pixel			n;

	if (x + 1 < env->map->points[y][0])
	{
		p.z = env->map->points[y][x];
		n.z = env->map->points[y][x + 1];
		n.y = y * env->map->coef - env->map->y * env->map->coef / 2;
		n.x = x * env->map->coef - env->map->x * env->map->coef / 2;
		fdf_pxl_proj(&n, n.z, env);
		fdf_draw_segment(p, n, env);
	}
	if (y + 1 < env->map->y)
	{
		p.z = env->map->points[y][x];
		n.z = env->map->points[y + 1][x];
		n.y = (y + 1) * env->map->coef - env->map->y * env->map->coef / 2;
		n.x = (x - 1) * env->map->coef - env->map->x * env->map->coef / 2;
		fdf_pxl_proj(&n, n.z, env);
		fdf_draw_segment(p, n, env);
	}
}
