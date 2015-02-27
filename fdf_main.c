/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vame <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/10 16:56:15 by vame              #+#    #+#             */
/*   Updated: 2015/02/16 15:09:32 by vame             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int				main(int av, char **ac)
{
	t_win		env;
	t_map		map;

	fdf_create_map(&map, av, ac);
	env.map = &map;
	env.mlx = mlx_init();
	fdf_set_color(KEYCODE_1, &env);
	fdf_calc_win_param(&env);
	env.win = mlx_new_window(env.mlx, env.w, env.h, "fdf");
	mlx_expose_hook(env.win, fdf_expose_hook, &env);
	mlx_key_hook(env.win, key_hook, &env);
	mlx_loop(env.mlx);
	return (0);
}
