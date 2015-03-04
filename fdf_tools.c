/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vame <vame@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/09 15:08:16 by vame              #+#    #+#             */
/*   Updated: 2015/03/04 09:43:37 by vame             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** ecrit un message d'erreur sur la sortie std et la sortie d'erreur
** en fonction du code erreur envoye (define dans fdf.h) puis quite le
** programme avec exit
*/

void	fdf_print_error(int err)
{
	if (err == ERR_ARG)
		ft_printf("{red}Bad number of arguments.{eoc}\n");
	if (err == ERR_MAP)
		ft_printf("{red}Bad format of map.{eoc}\n");
	if (err == ERR_MAL)
		ft_printf("{red}Malloc error.{eoc}\n");
	if (err == ERR_OPN)
		ft_printf("{red}Open error: file not found.{eoc}\n");
	if (err == ERR_RED)
		ft_printf("{red}Read error.{eoc}\n");
	if (err == ERR_CLS)
		ft_printf("{red}Close error.{eoc}\n");
	if (err == ERR_GNL)
		ft_printf("{red}Get_next_line error.{eoc}\n");
	exit(err);
}
