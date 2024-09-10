# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/29 15:52:05 by iberegsz          #+#    #+#              #
#    Updated: 2024/09/10 15:07:27 by iberegsz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:=	cub3D

CC		:=	cc
CFLAGS	:= -Wall -Wextra -Werror -g

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
			src/handle_image.c \
			src/handle_keys.c \
			src/handle_mouse.c \
			src/init_components.c \
			src/init_environment.c \
			src/parsing.c \
			src/map_utils.c \
			src/time_utils.c \
			src/raycasting.c \
			src/ray_drawing.c \
			src/ray_handlers.c \
			src/handle_sprites.c \
			src/doors.c \
			src/gradient.c \
			src/draw_player.c \
			src/draw_monster.c \
			src/draw_raycasting.c \
			src/draw_gunshot.c \
			src/draw_gunshot_helper.c \
			src/draw_utils.c \
			src/draw_dynamic_sprite.c \
			src/draw_sprites.c \
			src/is_entity.c \
			src/init_textures.c \
			src/init_sprites.c \
			src/player_move.c \
			src/handle_player.c \
			src/handle_enemies.c \
			src/handle_enemy_list.c \

# LIBS 
LIBS	:= libft/libft.a

# OBJECT FILES
OBJ_SRC	:= $(SRC:%.c=$(OBJDIR)/%.o)
OBJ_GNL	:= $(GNL:%.c=$(OBJDIR)/%.o)

$(shell mkdir -p $(OBJDIR) $(OBJDIR)/src $(OBJDIR)/gnl)

all		: $(NAME)

$(NAME)	: $(OBJ_SRC) $(OBJ_GNL) cub3d.h
	make -C libft all -j
	$(CC) $(OBJ_SRC) $(OBJ_GNL) $(LIBS) -lmlx -lXext -lX11 -lm -o $(NAME)

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
