/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_create_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vame <vame@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/09 14:59:30 by vame              #+#    #+#             */
/*   Updated: 2015/03/04 09:43:00 by vame             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** creation de la map :
** 1 - open le fichier indique en arguments
** 2 - use gnl pour recuperer les infos de la map
** 3 - stocker ces lignes dans un char **
** 4 - malloc et remplir le int ** de la map (points[y][x] = altitude) :
**		a - compter le nombre de lignes
**		b - allouer la premiere dimension avec le nombre de lignes
**		c - split chaque ligne dans un nouveau char **
**		d - compter le nombre le points de la ligne
**		e - allouer la deuxieme dimension avec le nombre de points
**		f - remplir les altitudes des points avec atoi
*/

char			**fdf_read_map(char *ac)
{
	int			fd;
	int			res;
	char		*line;
	char		**read;

	line = NULL;
	read = NULL;
	if ((fd = open(ac, O_RDONLY)) == -1)
		fdf_print_error(ERR_OPN);
	while ((res = get_next_line_2(fd, &line)) == 1)
		read = fdf_join_line(&line, &read);
	if (res == -1)
		fdf_print_error(ERR_GNL);
	if (close(fd) == -1)
		fdf_print_error(ERR_CLS);
	return (read);
}

char			**fdf_join_line(char **line, char ***read)
{
	size_t		i;
	size_t		len;
	char		**new;

	i = 0;
	len = 0;
	while (*read && (*read)[len])
		len++;
	if (!(new = (char **)malloc(sizeof(char *) * (len + 2))))
		fdf_print_error(ERR_MAL);
	new[len + 1] = NULL;
	while (i++ < len)
		new[i - 1] = (*read)[i - 1];
	new[len] = *line;
	if (*read)
		free(*read);
	return (new);
}

void			fdf_malloc_y_map(t_map *map, char **read)
{
	int			y;

	y = 0;
	while (read && read[y])
		y++;
	if (!y)
		fdf_print_error(ERR_MAP);
	if (!(map->points = (int **)malloc(sizeof(int *) * (y))))
		fdf_print_error(ERR_MAL);
	map->x = 0;
	map->y = y;
	map->z_min = INT_MAX;
	map->z_max = INT_MIN;
}

void			fdf_malloc_x_map(t_map *map, char **split, int y)
{
	int			x;

	x = 0;
	while (split && split[x])
		x++;
	if (!x)
		fdf_print_error(ERR_MAP);
	if (!(map->points[y - 1] = (int *)malloc(sizeof(int) * (x + 1))))
		fdf_print_error(ERR_MAL);
	map->points[y - 1][0] = x + 1;
	if (x > map->x)
		map->x = x;
}

void			fdf_create_map(t_map *map, int av, char **ac)
{
	int			y;
	int			x;
	char		**read;
	char		**split;

	if (!(y = 0) && av != 2)
		fdf_print_error(ERR_ARG);
	read = fdf_read_map(ac[1]);
	fdf_malloc_y_map(map, read);
	while (read && read[y++] && !(x = 0))
	{
		if (!(split = ft_nbrsplit(read[y - 1])))
			fdf_print_error(ERR_MAL);
		fdf_malloc_x_map(map, split, y);
		while (split && split[x++])
			map->points[y - 1][x] = fdf_create_alti(split[x - 1], map);
		ft_strdel_double(&split);
	}
	ft_strdel_double(&read);
}
