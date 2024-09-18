# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/29 15:52:05 by iberegsz          #+#    #+#              #
#    Updated: 2024/09/18 22:05:14 by iberegsz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:=	cub3D

CC		:=	cc
CFLAGS	:= -Wall -Wextra -Werror -g#3 -fsanitize=address,undefined,leak
#LDFLAGS := -fsanitize=address,undefined,leak
MLXFLAGS:= -lmlx -lXext -lX11 -lm

# DIRECTORIES
SRCDIR	:=	src
GNLDIR	:=	gnl
OBJDIR	:=	obj

# FILES
GNL		:=	gnl/get_next_line.c \
			gnl/get_next_line_utils.c \

SRC		:=	src/cub3d.c \
			src/draw_line.c \
			src/draw_environment.c \
			src/draw_entities.c \
			src/free_memory_utils.c \
			src/free_environment.c \
			src/free_components.c \
			src/free_sprites.c \
			src/free_textures.c \
			src/free_enemies.c \
			src/free_gun_and_fire.c \
			src/free_animated_frames.c \
			src/handle_image.c \
			src/handle_keys.c \
			src/handle_mouse.c \
			src/init_components.c \
			src/init_environment.c \
			src/init_enemy_sprites.c \
			src/parsing.c \
			src/map_utils.c \
			src/time_utils.c \
			src/raycasting.c \
			src/ray_drawing.c \
			src/ray_handlers.c \
			src/handle_sprites.c \
			src/gradient.c \
			src/draw_player.c \
			src/draw_monster.c \
			src/draw_raycasting.c \
			src/draw_gunshot.c \
			src/draw_gunshot_helper.c \
			src/draw_utils.c \
			src/draw_dynamic_sprite.c \
			src/draw_sprite_stripe.c \
			src/draw_sprites.c \
			src/is_entity.c \
			src/is_construction.c \
			src/init_textures.c \
			src/init_sprites.c \
			src/player_move.c \
			src/handle_player.c \
			src/handle_enemies.c \
			src/handle_enemy_list.c \
			src/init_animations.c \
			src/init_enemies.c \
			src/init_doors.c \
			src/load_animated_sprite.c \
			src/setup_enemies.c \
			src/parse_input.c \
			src/free_animations.c \
			src/handle_door_list.c \
			src/handle_objects.c \
			src/raycasting_utils.c \
			src/init_mlx.c \
			src/parse_map.c \
			src/parse_utils.c \
			src/parse_filename.c \
			src/parse_file_paths_and_colors.c \
			src/validate_line.c \
			src/read_map.c \
			src/ft_utils.c

# LIBS 
LIBS	:= libft/libft.a

# OBJECT FILES
OBJ_SRC	:= $(SRC:%.c=$(OBJDIR)/%.o)
OBJ_GNL	:= $(GNL:%.c=$(OBJDIR)/%.o)

$(shell mkdir -p $(OBJDIR) $(OBJDIR)/src $(OBJDIR)/gnl)

all		: $(NAME)

$(NAME)	: $(OBJ_SRC) $(OBJ_GNL) cub3d.h
	make -C libft all -j
	$(CC) $(OBJ_SRC) $(OBJ_GNL) $(LIBS) $(MLXFLAGS) -o $(NAME)
# $(LDFLAGS) -o $(NAME)

clean	:
	make -C libft clean -j
	rm -f $(OBJ_SRC) $(OBJ_GNL)

fclean	:
	make -C libft fclean -j
	rm -f $(OBJ_SRC) $(OBJ_GNL) $(NAME)

re		: fclean all

$(OBJDIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/gnl/%.o: gnl/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY	: all clean fclean re
