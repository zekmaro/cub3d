# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/29 15:52:05 by iberegsz          #+#    #+#              #
#    Updated: 2024/09/24 16:49:23 by iberegsz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:=	cub3D
BON_NAME:=	cub3D_bonus

CC		:=	cc
CFLAGS	:= -Wall -Wextra -Werror #-g3 -fsanitize=address,undefined,leak
#LDFLAGS := -fsanitize=address,undefined,leak
MLXFLAGS:= -lmlx -lXext -lX11 -lm

OBJDIR	:=	obj

# FILES
GNL		:=	gnl/get_next_line.c \
			gnl/get_next_line_utils.c \

SRC		:=	mandotary/cub3d.c \
			mandotary/draw_line.c \
			mandotary/draw_environment.c \
			mandotary/draw_entities.c \
			mandotary/free_memory_utils.c \
			mandotary/free_environment.c \
			mandotary/free_components.c \
			mandotary/free_sprites.c \
			mandotary/free_textures.c \
			mandotary/free_enemies.c \
			mandotary/free_gun_and_fire.c \
			mandotary/free_animated_frames.c \
			mandotary/handle_image.c \
			mandotary/handle_keys.c \
			mandotary/handle_mouse.c \
			mandotary/init_components.c \
			mandotary/init_environment.c \
			mandotary/init_enemy_sprites.c \
			mandotary/parsing.c \
			mandotary/map_utils.c \
			mandotary/time_utils.c \
			mandotary/raycasting.c \
			mandotary/ray_drawing.c \
			mandotary/ray_handlers.c \
			mandotary/handle_sprites.c \
			mandotary/gradient.c \
			mandotary/draw_player.c \
			mandotary/draw_monster.c \
			mandotary/draw_raycasting.c \
			mandotary/draw_gunshot.c \
			mandotary/draw_gunshot_helper.c \
			mandotary/draw_utils.c \
			mandotary/draw_dynamic_sprite.c \
			mandotary/draw_sprite_stripe.c \
			mandotary/draw_sprites.c \
			mandotary/is_entity.c \
			mandotary/is_construction.c \
			mandotary/init_textures.c \
			mandotary/init_sprites.c \
			mandotary/player_move.c \
			mandotary/handle_player.c \
			mandotary/handle_enemies.c \
			mandotary/handle_enemy_list.c \
			mandotary/init_animations.c \
			mandotary/init_enemies.c \
			mandotary/init_doors.c \
			mandotary/load_animated_sprite.c \
			mandotary/setup_enemies.c \
			mandotary/parse_input.c \
			mandotary/free_animations.c \
			mandotary/handle_door_list.c \
			mandotary/handle_objects.c \
			mandotary/raycasting_utils.c \
			mandotary/init_mlx.c \
			mandotary/parse_utils.c \
			mandotary/parse_filename.c \
			mandotary/parse_file_paths_and_colors.c \
			mandotary/validate_line.c \
			mandotary/read_map.c \
			mandotary/ft_utils.c \
			mandotary/handle_initial_line.c \
			mandotary/handle_gnl_errors.c \
			mandotary/handle_parsing_loop.c \

BNS		:=	bonus/cub3d_bonus.c \
			bonus/draw_line_bonus.c \
			bonus/draw_environment_bonus.c \
			bonus/draw_entities_bonus.c \
			bonus/free_memory_utils_bonus.c \
			bonus/free_environment_bonus.c \
			bonus/free_components_bonus.c \
			bonus/free_sprites_bonus.c \
			bonus/free_textures_bonus.c \
			bonus/free_enemies_bonus.c \
			bonus/free_gun_and_fire_bonus.c \
			bonus/free_animated_frames_bonus.c \
			bonus/handle_image_bonus.c \
			bonus/handle_keys_bonus.c \
			bonus/handle_mouse_bonus.c \
			bonus/init_components_bonus.c \
			bonus/init_environment_bonus.c \
			bonus/init_enemy_sprites_bonus.c \
			bonus/parsing_bonus.c \
			bonus/map_utils_bonus.c \
			bonus/time_utils_bonus.c \
			bonus/raycasting_bonus.c \
			bonus/ray_drawing_bonus.c \
			bonus/ray_handlers_bonus.c \
			bonus/handle_sprites_bonus.c \
			bonus/gradient_bonus.c \
			bonus/draw_player_bonus.c \
			bonus/draw_monster_bonus.c \
			bonus/draw_raycasting_bonus.c \
			bonus/draw_gunshot_bonus.c \
			bonus/draw_gunshot_helper_bonus.c \
			bonus/draw_utils_bonus.c \
			bonus/draw_dynamic_sprite_bonus.c \
			bonus/draw_sprite_stripe_bonus.c \
			bonus/draw_sprites_bonus.c \
			bonus/is_entity_bonus.c \
			bonus/is_construction_bonus.c \
			bonus/init_textures_bonus.c \
			bonus/init_sprites_bonus.c \
			bonus/player_move_bonus.c \
			bonus/handle_player_bonus.c \
			bonus/handle_enemies_bonus.c \
			bonus/handle_enemy_list_bonus.c \
			bonus/init_animations_bonus.c \
			bonus/init_enemies_bonus.c \
			bonus/init_doors_bonus.c \
			bonus/load_animated_sprite_bonus.c \
			bonus/setup_enemies_bonus.c \
			bonus/parse_input_bonus.c \
			bonus/free_animations_bonus.c \
			bonus/handle_door_list_bonus.c \
			bonus/handle_objects_bonus.c \
			bonus/raycasting_utils_bonus.c \
			bonus/init_mlx_bonus.c \
			bonus/parse_utils_bonus.c \
			bonus/parse_filename_bonus.c \
			bonus/parse_file_paths_and_colors_bonus.c \
			bonus/validate_line_bonus.c \
			bonus/read_map_bonus.c \
			bonus/ft_utils_bonus.c \
			bonus/handle_initial_line_bonus.c \
			bonus/handle_gnl_errors_bonus.c \
			bonus/handle_parsing_loop_bonus.c \

# LIBS 
LIBS	:= libft/libft.a

# OBJECT FILES
OBJ_SRC	:= $(SRC:%.c=$(OBJDIR)/%.o)
OBJ_GNL	:= $(GNL:%.c=$(OBJDIR)/%.o)
OBJ_BON	:= $(BNS:%.c=$(OBJDIR)/%.o)

MAKEFLAGS += -j$(nproc)

$(shell mkdir -p $(OBJDIR) $(OBJDIR)/src $(OBJDIR)/gnl $(OBJDIR)/bonus)

all		: $(NAME)

bonus	: $(BON_NAME)

$(NAME)	: $(OBJ_SRC) $(OBJ_GNL) cub3d.h
	$(MAKE) -C libft all
	$(CC) $(OBJ_SRC) $(OBJ_GNL) $(LIBS) $(MLXFLAGS) -o $(NAME)
# $(LDFLAGS) -o $(NAME)

$(BON_NAME)	: $(OBJ_BON) $(OBJ_GNL) cub3d.h
	$(MAKE) -C libft all
	$(CC) $(OBJ_BON) $(OBJ_GNL) $(LIBS) $(MLXFLAGS) -o $(BON_NAME)

clean	:
	$(MAKE) -C libft clean
	rm -f $(OBJ_SRC) $(OBJ_GNL)

fclean	:
	$(MAKE) -C libft fclean
	rm -f $(OBJ_SRC) $(OBJ_GNL) $(NAME)

re		:
	$(MAKE) -C libft fclean
	rm -f $(OBJ_SRC) $(OBJ_GNL) $(NAME)
	$(MAKE) all

$(OBJDIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/gnl/%.o: gnl/%.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY	: all clean fclean re bonus
