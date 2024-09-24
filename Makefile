# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/29 15:52:05 by iberegsz          #+#    #+#              #
#    Updated: 2024/09/24 18:23:21 by iberegsz         ###   ########.fr        #
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

SRC		:=	mandatory/cub3d.c \
			mandatory/draw_line.c \
			mandatory/draw_environment.c \
			mandatory/draw_entities.c \
			mandatory/free_memory_utils.c \
			mandatory/free_environment.c \
			mandatory/free_components.c \
			mandatory/free_sprites.c \
			mandatory/free_textures.c \
			mandatory/free_enemies.c \
			mandatory/free_gun_and_fire.c \
			mandatory/free_animated_frames.c \
			mandatory/handle_image.c \
			mandatory/handle_keys.c \
			mandatory/handle_mouse.c \
			mandatory/init_components.c \
			mandatory/init_environment.c \
			mandatory/init_enemy_sprites.c \
			mandatory/parsing.c \
			mandatory/map_utils.c \
			mandatory/time_utils.c \
			mandatory/raycasting.c \
			mandatory/ray_drawing.c \
			mandatory/ray_handlers.c \
			mandatory/handle_sprites.c \
			mandatory/gradient.c \
			mandatory/draw_player.c \
			mandatory/draw_monster.c \
			mandatory/draw_raycasting.c \
			mandatory/draw_gunshot.c \
			mandatory/draw_gunshot_helper.c \
			mandatory/draw_utils.c \
			mandatory/draw_dynamic_sprite.c \
			mandatory/draw_sprite_stripe.c \
			mandatory/draw_sprites.c \
			mandatory/is_entity.c \
			mandatory/is_construction.c \
			mandatory/init_textures.c \
			mandatory/init_sprites.c \
			mandatory/player_move.c \
			mandatory/handle_player.c \
			mandatory/handle_enemies.c \
			mandatory/handle_enemy_list.c \
			mandatory/init_animations.c \
			mandatory/init_enemies.c \
			mandatory/init_doors.c \
			mandatory/load_animated_sprite.c \
			mandatory/setup_enemies.c \
			mandatory/parse_input.c \
			mandatory/free_animations.c \
			mandatory/handle_door_list.c \
			mandatory/handle_objects.c \
			mandatory/raycasting_utils.c \
			mandatory/init_mlx.c \
			mandatory/parse_utils.c \
			mandatory/parse_filename.c \
			mandatory/parse_file_paths_and_colors.c \
			mandatory/validate_line.c \
			mandatory/read_map.c \
			mandatory/ft_utils.c \
			mandatory/handle_initial_line.c \
			mandatory/handle_gnl_errors.c \
			mandatory/handle_parsing_loop.c \

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

$(shell mkdir -p $(OBJDIR) $(OBJDIR)/mandatory $(OBJDIR)/gnl $(OBJDIR)/bonus)

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
	rm -f $(OBJ_SRC) $(OBJ_GNL) $(OBJ_BON)

fclean	:
	$(MAKE) -C libft fclean
	rm -f $(OBJ_SRC) $(OBJ_GNL) $(OBJ_BON) $(NAME) $(BON_NAME)

re		:
	$(MAKE) -C libft fclean
	rm -f $(OBJ_SRC) $(OBJ_GNL)  $(OBJ_BON) $(NAME) $(BON_NAME)
	$(MAKE) all

$(OBJDIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/gnl/%.o: gnl/%.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY	: all clean fclean re bonus
