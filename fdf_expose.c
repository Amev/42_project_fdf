/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_expose.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vame <vame@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/16 10:50:51 by vame              #+#    #+#             */
/*   Updated: 2015/02/16 17:02:30 by vame             ###   ########.fr       */
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

int				fdf_expose_hook(t_win *env)
{
	env->img = mlx_new_image(env->mlx, env->w - 19, env->h - 19);
	env->img_str = mlx_get_data_addr(env->img, &env->bpp, &env->len, &env->endian);
	fdf_draw(env);
	mlx_put_image_to_window(env->mlx, env->win, env->img, 10, 10);
	mlx_destroy_image(env->mlx, env->img);
	return (1);
}
