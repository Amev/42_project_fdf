# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vame <vame@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/01/23 11:23:10 by vame              #+#    #+#              #
#    Updated: 2015/03/04 10:08:55 by vame             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

CFLAGS = -Werror -Wextra -Wall -I libft/includes/

LIBX = -lm -L libft/ -lft -L /usr/x11/lib -lmlx -lXext -lX11

INC = ./fdf.h

TMP = $(INC:.h=.h.gch)

SRC =	./fdf_main.c \
		./fdf_draw.c \
		./fdf_tools.c \
		./fdf_window.c \
		./fdf_expose.c \
		./fdf_matrix.c \
		./fdf_filling.c \
		./fdf_key_hook.c \
		./fdf_index_alti.c \
		./fdf_create_map.c \
		./fdf_matrix_tools.c \
		./fdf_color_degrade.c

BINAIRE = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(BINAIRE)
		@make -C libft/
		gcc -g -o $(NAME) $(BINAIRE) $(LIBX)
		@rm -f $(TMP)

lib :
		@make -C libft/ fclean
		@make -C libft/

clean:
		rm -f $(BINAIRE)
		@make -C libft/ clean

fclean: clean
		rm -f $(NAME)
		@make -C libft/ fclean

re: fclean all

.PHONY: all lib clean fclean re
