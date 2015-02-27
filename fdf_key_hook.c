/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_key_hook.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vame <vame@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/09 15:07:36 by vame              #+#    #+#             */
/*   Updated: 2015/02/27 16:53:54 by vame             ###   ########.fr       */
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
		printf("-- tx = %f. --\n", env->m.tx);
	}
	if (keycode == 65362 || keycode == 65364)
	{
		env->m.tx += keycode == 65362 ? -20.00 : 20.00;
		env->m.ty += keycode == 65362 ? -20.00 : 20.00;
		printf("-- ty = %f. --\n", env->m.ty);
	}
	if (keycode == 119 || keycode == 115)
		env->m.ax += keycode == 119 ? PI / 12 : -PI / 12;
	if (keycode == 113 || keycode == 101)
		env->m.ay += keycode == 119 ? PI / 12 : -PI / 12;
	if (keycode == 97 || keycode == 100)
		env->m.az += keycode == 119 ? PI / 12 : -PI / 12;
	fdf_matrix_init(env);
	fdf_expose_hook(env);
}

int					key_hook(int keycode, t_win *env)
{
	(void)env;
	if (keycode == 65307)
		exit(0);
	else if (keycode == KEYCODE_1 || keycode == KEYCODE_2
			|| keycode == KEYCODE_3)
	{
		fdf_set_color(keycode, env);
		fdf_expose_hook(env);
	}
	else if (keycode == 65453 || keycode == 65451)
		fdf_key_change_coef_z(env, keycode);
	else if (keycode == 65361 || keycode == 65362 || keycode == 65363 ||
				keycode == 65364 || keycode == 119 || keycode == 115 ||
			keycode == 113 || keycode == 101 || keycode == 97 || keycode == 100)
		fdf_key_transform(env, keycode);
	ft_printf("-- keycode = %d. --\n", keycode);
	return (0);
}
