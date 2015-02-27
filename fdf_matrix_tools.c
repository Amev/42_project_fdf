/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_matrix_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vame <vame@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/27 14:36:53 by vame              #+#    #+#             */
/*   Updated: 2015/02/27 15:27:29 by vame             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

float				**fdf_create_mat(int x, int y)
{
	int				i;
	float			**new;

	i = 0;
	if (!(new = (float **)malloc(sizeof(float *) * y)))
		fdf_print_error(ERR_MAL);
	while (i < y)
		if (!(new[i++] = (float *)malloc(sizeof(float) * x)))
			fdf_print_error(ERR_MAL);
	return (new);
}

void				fdf_del_mat(int x, float ***mat)
{
	int				i;

	i = 0;
	while (i < x)
	{
		free((*mat)[i]);
		(*mat)[i++] = NULL;
	}
	free(*mat);
	*mat = NULL;
}
