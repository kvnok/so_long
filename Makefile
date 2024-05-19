NAME = so_long
CC = cc
CFLAGS = -Wall -Wextra -Werror

MLXLIB = libmlx42.a
MLXFLAGS = -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit

SRC = cleaning.c error_checks.c error_print_etc.c ft_split.c get_next_line_utils.c get_next_line.c \
key_collectable_exit.c main.c make_map.c move_wasd.c pathfinding.c pngs_images_instances.c
OBJ = $(SRC:%.c=./obj/%.o)
OBJDIR = obj

all: $(NAME)

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(MLXLIB):
	@cd ./MLX42 && cmake -B build && make -C build -j4
	@cd ./MLX42/build && cp libmlx42.a ../../

$(OBJDIR)/%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(MLXLIB) $(OBJDIR) $(OBJ)
	@$(CC) $(MLXFLAGS) $(MLXLIB) $(OBJ) -o $(NAME)

clean:
	@rm -rf $(OBJDIR)

fclean: clean
	@cd ./MLX42 && rm -rf build
	@rm -rf $(MLXLIB)
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
