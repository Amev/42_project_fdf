/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_key_hook.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vame <vame@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/09 15:07:36 by vame              #+#    #+#             */
/*   Updated: 2015/02/26 09:55:42 by vame             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fdf_set_color(int keycode, t_win *env)
{
	if (keycode == KEYCODE_1)
	{
		env->color->color1 = 0x000066;
		env->color->color2 = 0x0066FF;
		env->color->color3 = 0xFFFF00;
		env->color->color4 = 0x009933;
		env->color->color5 = 0x663300;
		env->color->color6 = 0xC7B5A2;
		env->color->color7 = 0xFFFFFF;
	}
	else if (keycode == KEYCODE_2)
	{
		env->color->color1 = 0x0000FF;
		env->color->color2 = 0x00FFFF;
		env->color->color3 = 0x00FF00;
		env->color->color4 = 0xFBFF00;
		env->color->color5 = 0xFF671E;
		env->color->color6 = 0xFF0000;
		env->color->color7 = 0x000000;
	}
	else if (keycode == KEYCODE_3)
	{
		env->color->color1 = 0x000000;
		env->color->color2 = 0xFFFFFF;
		env->color->color3 = 0x000000;
		env->color->color4 = 0x464646;
		env->color->color5 = 0x8B8B8B;
		env->color->color6 = 0xD1D1D1;
		env->color->color7 = 0xFFFFFF;
	}
}

void	fdf_key_change_coef_z(t_win *env, int keycode)
{
	if (keycode == 65451)
		env->coef_z *= 2;
	else if (keycode == 65453 && env->coef_z > 0)
		env->coef_z /= 2;
	fdf_expose_hook(env);
}

int		key_hook(int keycode, t_win *env)
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
	//ft_printf("-- keycode = %d. --\n", keycode);
	return (0);
}
