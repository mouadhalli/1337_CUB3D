# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mhalli <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/27 11:40:36 by mhalli            #+#    #+#              #
#    Updated: 2021/01/27 11:40:40 by mhalli           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: re clean fclean

NAME = cub3D

LIBS = libft/libft.a \

CC = gcc

FLAGS = -Wall -Werror -Wextra -g -fsanitize=address\
	  -I /usr/local/include \
	  -L /usr/local/lib -lmlx \
	  -framework OpenGL -framework AppKit \

MAKE = make -C

SRC = GNL/get_next_line.c file_reading.c utils.c file_utils.c rays.c player.c walls.c sprite.c vertical_rays.c horizontal_rays.c cub3d.c map_reading.c analyse_map.c screenshot.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME):
	@$(MAKE) libft
	@$(CC) $(FLAGS) $(SRC) $(LIBS) -o $(NAME)

clean:
	@$(MAKE) libft clean
	@rm -rf $(OBJ)

fclean: clean
	@$(MAKE) libft fclean
	@rm -f cub3D

re:	fclean all
