/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_matrix.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vame <vame@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/26 13:00:17 by vame              #+#    #+#             */
/*   Updated: 2015/02/27 16:53:55 by vame             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void			fdf_clean_mat(float ***matrix)
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

static void			fdf_matrix_calc(float **a, float **b, t_win *env)
{
	int				x;
	int				y;
	int				z;
	float			**res;

	y = 0;
	res = fdf_create_mat(4, 4);
	while (y < 4)
	{
		x = 0;
		while (x < 4)
		{
			z = 0;
			res[y][x] = 0;
			while (z++ < 4)
				res[y][x] += a[y][z - 1] * b[z - 1][x];
			x++;
		}
		y++;
	}
	if (env->m.main)
		fdf_del_mat(4, &(env->m.main));
	env->m.main = res;
}

static void			fdf_print_main(t_win *env)
{
	int				i;
	int				j;

	j = 0;
	while (j < 4)
	{
		i = 0;
		while (i < 4)
			printf("%f ", env->m.main[j][i++]);
		printf("\n");
		j++;
	}
	printf("--------------------------------------\n");
}

static void			fdf_matrix_combo(t_win *env)
{
	fdf_clean_mat(&(env->m.main));
	fdf_print_main(env);
	fdf_matrix_calc(env->m.m_t, env->m.main, env);
	fdf_print_main(env);
	fdf_matrix_calc(env->m.m_rx, env->m.main, env);
	fdf_print_main(env);
	fdf_matrix_calc(env->m.m_ry, env->m.main, env);
	fdf_print_main(env);
	fdf_matrix_calc(env->m.m_rz, env->m.main, env);
	fdf_print_main(env);
	fdf_matrix_calc(env->m.m_s, env->m.main, env);
	fdf_print_main(env);
}

void				fdf_matrix_init(t_win *env)
{
	fdf_clean_mat(&(env->m.m_t));
	env->m.m_t[0][3] = env->m.tx;
	env->m.m_t[1][3] = env->m.ty;
	env->m.m_t[2][3] = env->m.tz;
	fdf_clean_mat(&(env->m.m_s));
	env->m.m_s[0][0] = env->m.sx;
	env->m.m_s[1][1] = env->m.sy;
	env->m.m_s[2][2] = env->m.sz;
	fdf_clean_mat(&(env->m.m_rx));
	env->m.m_rx[1][1] = cos(env->m.ax);
	env->m.m_rx[1][2] = -sin(env->m.ax);
	env->m.m_rx[2][1] = sin(env->m.ax);
	env->m.m_rx[2][2] = cos(env->m.ax);
	fdf_clean_mat(&(env->m.m_ry));
	env->m.m_ry[0][0] = cos(env->m.ay);
	env->m.m_ry[0][2] = sin(env->m.ay);
	env->m.m_ry[2][0] = -sin(env->m.ay);
	env->m.m_ry[2][2] = cos(env->m.ay);
	fdf_clean_mat(&(env->m.m_rz));
	env->m.m_rz[0][0] = cos(env->m.az);
	env->m.m_rz[0][1] = -sin(env->m.az);
	env->m.m_rz[1][0] = sin(env->m.az);
	env->m.m_rz[1][1] = cos(env->m.az);
	fdf_matrix_combo(env);
}

void				fdf_matrix_bzero(t_win *env)
{
	env->m.tx = 0;
	env->m.ty = 0;
	env->m.tz = 0;
	env->m.ax = 0;
	env->m.ay = 0;
	env->m.az = 0;
	env->m.sx = 1;
	env->m.sy = 1;
	env->m.sz = 1;
	env->m.m_t = fdf_create_mat(4, 4);
	env->m.m_s = fdf_create_mat(4, 4);
	env->m.m_rx = fdf_create_mat(4, 4);
	env->m.m_ry = fdf_create_mat(4, 4);
	env->m.m_rz = fdf_create_mat(4, 4);
	env->m.main = fdf_create_mat(4, 4);
	fdf_matrix_init(env);
}
