/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_matrix.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vame <vame@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/26 13:00:17 by vame              #+#    #+#             */
/*   Updated: 2015/02/26 17:07:52 by vame             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void				fdf_matrix_init(float ***matrix)
{
	int				x;
	int				y;

	y = 0;
	while (y < 4)
	{
		x = 0;
		while (x < 4)
			(*matrix)[y][x++] = 0;
		y++;
	}
	(*matrix)[0][0] = 1;
	(*matrix)[1][1] = 1;
	(*matrix)[2][2] = 1;
	(*matrix)[3][3] = 1;
}

float				**fdf_matrix_calc(float **a, float **b, t_win *env)
{
	int				x;
	int				y;
	int				z;

	while (y < 4)
	{
		x = 0;
		while (x < 4)
		{
			z = 0;
			env->m->main[y][x] = 0;
			while (z++ < 4)
				env->m->main[y][x] += a[y][z - 1] * b[z - 1][x];
			x++;
		}
		y++
	}
}

void				fdf_matrix_combo(t_win *env)
{
	fdf_matrix_calc(env->m->m_t, env->m->m_rx, env);
	fdf_matric_calc(env->m->m_ry, env->m->main, env);
	fdf_matric_calc(env->m->m_rz, env->m->main, env);
	fdf_matric_calc(env->m->m_s, env->m->main, env);
}

void				fdf_matrix_init(t_win *env)
{
	fdf_matrix_init(&(env->m->m_t));
	env->m->m_t[0][3] = env->m->tx;
	env->m->m_t[1][3] = env->m->ty;
	env->m->m_t[2][3] = env->m->tz;
	fdf_matrix_init(&(env->m->m_s));
	env->m->m_s[0][0] = env->m->sx;
	env->m->m_s[1][1] = env->m->sy;
	env->m->m_s[2][2] = env->m->sz;
	fdf_matrix_init(&(env->m->m_rx));
	env->m->m_rx[1][1] = cos(env->m->ax);
	env->m->m_rx[1][2] = -sin(env->m->ax);
	env->m->m_rx[2][1] = sin(env->m->ax);
	env->m->m_rx[2][2] = cos(env->m->ax);
	fdf_matrix_init(&(env->m->m_ry));
	env->m->m_ry[0][0] = cos(env->m->ay);
	env->m->m_ry[0][2] = sin(env->m->ay);
	env->m->m_ry[2][0] = -sin(env->m->ay);
	env->m->m_ry[2][2] = cos(env->m->ay);
	fdf_matrix_init(&(env->m->m_rz));
	env->m->m_rz[0][0] = cos(env->m->az);
	env->m->m_rz[0][1] = -sin(env->m->az);
	env->m->m_rz[1][0] = sin(env->m->az);
	env->m->m_rz[1][1] = cos(env->m->az);
	fdf_matrix_combo(env);
}

void				fdf_matrix_bzero(t_win *env)
{
	env->m->tx = 0;
	env->m->ty = 0;
	env->m->tz = 0;
	env->m->ax = 0;
	env->m->ay = 0;
	env->m->az = 0;
	env->m->sx = 0;
	env->m->sy = 0;
	env->m->sz = 0;
	fdf_matrix_init(env);
	fdf_matrix_combo(env);
}
