/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_index_alti.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vame <vame@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/11 10:41:41 by vame              #+#    #+#             */
/*   Updated: 2015/02/26 17:07:54 by vame             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int					fdf_create_alti(char *split, t_map *map)
{
	int				res;

	res = ft_atoi(split);
	if (map->z_min == INT_MAX && map->z_max == INT_MIN)
	{
		map->z_min = res;
		map->z_max = res;
	}
	else if (res < map->z_min)
		map->z_min = res;
	else if (res > map->z_max)
		map->z_max = res;
	return (res);
}

static void			fdf_index_alti_2(float alti, t_win *env, t_pixel *pxl)
{
	int				z;

	if (alti <= 35 * env->map->z_max / 100)
	{
		z = (35 * env->map->z_max / 100) - (5 * env->map->z_max / 100);
		pxl->color_a = env->color->color4;
		pxl->color_b = env->color->color5;
		pxl->index = (alti - (5 * env->map->z_max / 100)) * 100 / z;
	}
	else if (alti <= 60 * env->map->z_max / 100)
	{
		z = (60 * env->map->z_max / 100) - (35 * env->map->z_max / 100);
		pxl->color_a = env->color->color5;
		pxl->color_b = env->color->color6;
		pxl->index = (alti - (35 * env->map->z_max / 100)) * 100 / z;
	}
	else
	{
		z = env->map->z_max - (60 * env->map->z_max / 100);
		pxl->color_a = env->color->color6;
		pxl->color_b = env->color->color7;
		pxl->index = (alti - (60 * env->map->z_max / 100)) * 100 / z;
	}
}

void				fdf_index_alti(float alti, t_win *env, t_pixel *pxl)
{
	int				z;

	if (alti < 0)
	{
		z = env->map->z_min;
		pxl->color_a = env->color->color2;
		pxl->color_b = env->color->color1;
		pxl->index = alti * 100 / z;
	}
	else if (alti <= 3 * env->map->z_max / 1000)
	{
		z = 3 * env->map->z_max / 1000;
		pxl->color_a = env->color->color2;
		pxl->color_b = env->color->color3;
		pxl->index = alti == 0 ? 0 : alti * 100 / z;
	}
	else if (alti <= 5 * env->map->z_max / 100)
	{
		z = 5 * env->map->z_max / 100 - (3 * env->map->z_max / 1000);
		pxl->color_a = env->color->color3;
		pxl->color_b = env->color->color4;
		pxl->index = (alti - (3 * env->map->z_max / 1000)) * 100 / z;
	}
	else
		fdf_index_alti_2(alti, env, pxl);
}
