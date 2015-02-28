/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_window.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vame <vame@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/10 16:16:52 by vame              #+#    #+#             */
/*   Updated: 2015/02/28 15:15:48 by vame             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void			fdf_win_init_coef_z(t_win *e)
{
	int				z_max;

	e->coef_z = 1;
	z_max = e->map->z_max;
	if (ft_abs(e->map->z_max) > z_max)
		z_max = ft_abs(e->map->z_max);
	while (z_max / 10 > 10)
	{
		e->coef_z /= 10;
		z_max /= 10;
	}
}

void				fdf_calc_win_param(t_win *e)
{
	float			x_max;
	float			y_max;
	float			x_min;
	float			y_min;

	if (e->map->x < 1100 && e->map->y < 1100)
		e->map->coef = 1100 / (e->map->x > e->map->y ? e->map->x : e->map->y);
	else
		e->map->coef = 1;
	fdf_win_init_coef_z(e);
	e->w = (e->map->x - 1) * e->map->coef + 20;
	e->h = (e->map->y - 1) * e->map->coef + 20;
	x_min = sqrt(2) * (-(e->map->y - 1)) * e->map->coef / 2;
	y_min = (e->map->y - 1) * e->map->coef / sqrt(6);
	x_max = sqrt(2) * ((e->map->x - 1) * e->map->coef) / 2;
	y_max = (e->map->x - 1) * e->map->coef / sqrt(6);
	//e->w = sqrt(pow(y_min - y_max, 2) + pow(x_min - x_max, 2)) + 20;
	e->w = x_max - x_min + 20;
	e->o_x = (x_max - x_min) / 2;
	x_min = 0;
	y_min = sqrt(2) / sqrt(3) * e->map->z_max * e->coef_z;
	x_max = sqrt(2) * (e->map->x - e->map->y) * e->map->coef / 2;
	y_max = sqrt(2) / sqrt(3) * e->map->z_min * e->coef_z;
	y_max -= (((e->map->x - 1) + (e->map->y - 1)) * e->map->coef / sqrt(6));
	//e->h = sqrt(pow(y_min - y_max, 2) + pow(x_min - x_max, 2)) + 20;
	e->h = y_min - y_max + 20;
	e->o_y = (y_min - y_max) / 2;
}
