/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_expose.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vame <vame@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/16 10:50:51 by vame              #+#    #+#             */
/*   Updated: 2015/02/28 16:58:12 by vame             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** Fonction de "rafraichissement" de l'image :
**	1. Cree une image avec mlx_new_image
**	2. Initialise la nouvelle image avec mlx_get_data_addr
**	3. Envoi la nouvelle image a fdf_draw pour qu'elle soit "remplie"
**	4. Affiche l'image dans la fenetre
**	5. Detruit l'image une fois celle-ci affichee
*/

int				fdf_loop_hook(t_win *env)
{
	if (env->rot_on)
	{
		env->m.az += env->rot_on == 1 ? PI / 300 : -PI / 300;
		if (env->rot_plus > 0)
			env->m.ay += env->rot_on == 1 ? PI / 300 : -PI / 300;
		if (env->rot_plus > 1)
			env->m.ax += env->rot_on == 1 ? PI / 300 : -PI / 300;
		if (env->rot_plus > 2)
			env->rot_plus = 2;
		if (env->rot_plus < -2)
			env->rot_plus = -2;
		fdf_matrix_init(env);
		fdf_expose_hook(env);
	}
	return (1);
}

int				fdf_expose_hook(t_win *env)
{
	env->img = mlx_new_image(env->mlx, env->w - 19, env->h - 19);
	env->img_str = mlx_get_data_addr(env->img, &env->bpp, &env->len, &env->endian);
	fdf_draw(env);
	mlx_put_image_to_window(env->mlx, env->win, env->img, 10, 10);
	mlx_destroy_image(env->mlx, env->img);
	return (1);
}
