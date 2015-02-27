/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vame <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/14 14:53:46 by vame              #+#    #+#             */
/*   Updated: 2015/02/13 16:15:28 by vame             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "../libft/libft.h"
# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <limits.h>

# define BUFF_SIZE 2048

typedef struct			s_gnl_list
{
	char				*mem;
	int					index_fd;
	int					test;
	struct s_gnl_list	*nxt;
	struct s_gnl_list	*prv;
}						t_gnl_list;

typedef struct			s_buff
{
	char				mem[BUFF_SIZE + 1];
	int					index;
}						t_buff;

int						get_next_line(int const fd, char **line);
int						get_next_line_2(int const fd, char **line);

#endif
