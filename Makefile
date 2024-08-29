# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/29 15:52:05 by iberegsz          #+#    #+#              #
#    Updated: 2024/08/29 15:52:06 by iberegsz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= cub3D
CC		:= cc
OBJDIR	:= obj
SRC		:=	get_next_line/get_next_line.c \
			get_next_line/get_next_line_utils.c \
			cub3d.c \
			parsing.c \
			inits.c \
			utils.c \
			handle_image.c \
			handle_keys.c \
			drawing.c \
			draw_line.c
			
CFLAGS	:= -Wall -Wextra -Werror -g
LIBS	:= libft/libft.a minilibx_macos/libmlx.a
OBJ		:= $(SRC:%.c=%.o)

# $(shell mkdir -p $(OBJDIR))

all		: $(NAME)

$(NAME)	: $(OBJ) cub3d.h
	make -C libft all -j
	$(CC) $(OBJ) $(LIBS) -lmlx -lXext -lX11 -lm -o $(NAME)

clean	:
	make -C libft clean -j
	rm -f $(OBJ)

fclean	:
	make -C libft fclean -j
	rm -f $(OBJ) $(NAME)

re		: fclean all

$(OBJDIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY	: all clean fclean re