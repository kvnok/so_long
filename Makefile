SHELL := /bin/bash

NAME := so_long

SRC_FILES	:=	cleaning.c \
				error_checks.c \
				error_print_etc.c \
				ft_split.c \
				get_next_line_utils.c \
				get_next_line.c \
				key_collectable_exit.c \
				main.c \
				make_map.c \
				move_wasd.c \
				pathfinding.c \
				pngs_images_instances.c \

SRC_DIR := ./
OBJ_DIR := obj
MLX_DIR := MLX42

OBJ_FILES := $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

# SRC_SUBD = $(shell find $(SRC_DIR) -type d)
# OBJ_SUBD = $(subst $(SRC_DIR), $(OBJ_DIR), $(SRCSUBD))

MLX42 := $(MLX_DIR)/build/libmlx42.a

CC  := cc
IFLAGS := -I$(MLX_DIR)/include -I$(MLX_DIR)/include/$(MLX_DIR)
CFLAGS := -Wall -Wextra -Werror -MMD -MP -g
LFLAGS := -L$(MLX_DIR)/build -lmlx42 -lglfw -ldl -pthread -lm

all: $(MLX42) $(NAME)

$(MLX42):
	git submodule update --init
	@cmake $(MLX_DIR) -B $(MLX_DIR)/build
	$(MAKE) -C $(MLX_DIR)/build -j4

$(NAME): $(OBJ_FILES)
	$(CC) $^ -o $@ $(LFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

clean:
	@$(MAKE) clean -C $(MLX_DIR)/build -j4
	rm -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) clean/fast -C $(MLX_DIR)/build -j4
	-rm -f $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re
