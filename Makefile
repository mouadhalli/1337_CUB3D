NAME = cub3D

LIBS = libft/libft.a \

CC = clang

FLAGS = -Wall -Werror -Wextra \
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
	@rm cub3D

re:	fclean all