# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vame <vame@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/01/23 11:23:10 by vame              #+#    #+#              #
#    Updated: 2015/02/26 14:17:05 by vame             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

CFLAGS = -Werror -Wextra -Wall -O3 -I libft/includes/

INC = ./fdf.h

TMP = $(INC:.h=.h.gch)

SRC =	./fdf_main.c \
		./fdf_draw.c \
		./fdf_tools.c \
		./fdf_window.c \
		./fdf_expose.c \
		./fdf_key_hook.c \
		./fdf_index_alti.c \
		./fdf_create_map.c \
		./fdf_color_degrade.c

BINAIRE = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(BINAIRE)
		@make -C libft/
		gcc -g -o $(NAME) $(BINAIRE) -lm -L libft/ -lft -L /usr/x11/lib -lmlx -lXext -lX11
		@rm -f $(TMP)
		@make clean

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
