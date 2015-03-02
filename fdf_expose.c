/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_expose.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vame <vame@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/16 10:50:51 by vame              #+#    #+#             */
/*   Updated: 2015/03/02 14:16:28 by vame             ###   ########.fr       */
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
		env->m.az += env->rot_on == 1 ? PI / 400 : -PI / 400;
		if (env->rot_plus > 0)
			env->m.ay += env->rot_on == 1 ? PI / 400 : -PI / 400;
		if (env->rot_plus > 1)
			env->m.ax += env->rot_on == 1 ? PI / 400 : -PI / 400;
		if (env->rot_plus > 2)
			env->rot_plus = 2;
		if (env->rot_plus < -2)
			env->rot_plus = -2;
		fdf_matrix_init(env);
		fdf_expose_hook(env);
	}
	return (1);
}

int				fdf_expose_hook(t_win *e)
{
	e->img = mlx_new_image(e->mlx, e->w - 19, e->h - 19);
	e->img_str = mlx_get_data_addr(e->img, &e->bpp, &e->len, &e->endian);
	fdf_draw(e);
	mlx_put_image_to_window(e->mlx, e->win, e->img, 10, 10);
	mlx_destroy_image(e->mlx, e->img);
	return (1);
}
