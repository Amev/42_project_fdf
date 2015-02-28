/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_key_hook.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vame <vame@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/09 15:07:36 by vame              #+#    #+#             */
/*   Updated: 2015/02/28 16:58:11 by vame             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void				fdf_set_color(int keycode, t_win *env)
{
	if (keycode == KEYCODE_1)
	{
		env->color.color1 = 0x000066;
		env->color.color2 = 0x0066FF;
		env->color.color3 = 0xFFFF00;
		env->color.color4 = 0x009933;
		env->color.color5 = 0x663300;
		env->color.color6 = 0xC7B5A2;
		env->color.color7 = 0xFFFFFF;
	}
	else if (keycode == KEYCODE_2)
	{
		env->color.color1 = 0x0000FF;
		env->color.color2 = 0x00FFFF;
		env->color.color3 = 0x00FF00;
		env->color.color4 = 0xFBFF00;
		env->color.color5 = 0xFF671E;
		env->color.color6 = 0xFF0000;
		env->color.color7 = 0x000000;
	}
	else if (keycode == KEYCODE_3)
	{
		env->color.color1 = 0x000000;
		env->color.color2 = 0xFFFFFF;
		env->color.color3 = 0x000000;
		env->color.color4 = 0x464646;
		env->color.color5 = 0x8B8B8B;
		env->color.color6 = 0xD1D1D1;
		env->color.color7 = 0xFFFFFF;
	}
}

void				fdf_key_change_coef_z(t_win *env, int keycode)
{
	if (keycode == 65451)
		env->coef_z *= 2;
	else if (keycode == 65453 && env->coef_z > 0)
		env->coef_z /= 2;
	fdf_expose_hook(env);
}

void				fdf_key_transform(t_win *env, int keycode)
{
	if (keycode == 65361 || keycode == 65363)
	{
		env->m.tx += keycode == 65361 ? -20.00 : 20.00;
		env->m.ty += keycode == 65361 ? 20.00 : -20.00;
	}
	if (keycode == 65362 || keycode == 65364)
	{
		env->m.tx += keycode == 65362 ? -20.00 : 20.00;
		env->m.ty += keycode == 65362 ? -20.00 : 20.00;
	}
	if (keycode == 119 || keycode == 115)
		env->m.ax += keycode == 119 ? PI / 12 : -PI / 12;
	if (keycode == 113 || keycode == 101)
		env->m.ay += keycode == 113 ? PI / 12 : -PI / 12;
	if (keycode == 97 || keycode == 100)
		env->m.az += keycode == 97 ? PI / 12 : -PI / 12;
	if (keycode ==  61 || keycode == 45)
	{
		env->m.sx *= keycode == 61 ? 2 : 0.5;
		env->m.sy *= keycode == 61 ? 2 : 0.5;
	}
	if (keycode == 65288)
		fdf_matrix_bzero(env);
	else
		fdf_matrix_init(env);
	fdf_expose_hook(env);
}

int					key_hook(int k, t_win *env)
{
	if (env->rot_on && k != 44 && k != 46 && k != 47 && k != 109)
	{
		env->rot_on = 0;
		env->rot_plus = 0;
	}
	if (k == 65307)
		exit(0);
	else if (k == KEYCODE_1 || k == KEYCODE_2 || k == KEYCODE_3)
	{
		fdf_set_color(k, env);
		fdf_expose_hook(env);
	}
	else if (k == 65453 || k == 65451)
		fdf_key_change_coef_z(env, k);
	else if (k == 65361 || k == 65362 || k == 65363 || k == 65364 || k == 119
				|| k == 115 || k == 113 || k == 101 || k == 97 || k == 100 ||
			k == 65288 || k == 45 || k == 61)
		fdf_key_transform(env, k);
	else if (k == 44 || k == 46)
		env->rot_on = k == 44 ? 1 : 2;
	else if (env->rot_on && (k == 47 || k == 109))
		env->rot_plus += k == 47 ? 1 : -1;
	ft_printf("-- keycode = %d. --\n", k);
	return (0);
}
