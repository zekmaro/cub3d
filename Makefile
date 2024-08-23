NAME	:= cub3d
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
			drawing.c 
			
CFLAGS	:= -Wall -Wextra -g
LIBS	:= libft/libft.a minilibx_macos/libmlx.a
OBJ		:= $(SRC:%.c=%.o)

# $(shell mkdir -p $(OBJDIR))

all		: $(NAME)

$(NAME)	: $(OBJ) cub3d.h
	make -C libft all
	$(CC) $(OBJ) $(LIBS) -lmlx -lXext -lX11 -lm -o $(NAME)

clean	:
	make -C libft clean
	rm -f $(OBJ)

fclean	:
	make -C libft fclean
	rm -f $(OBJ) $(NAME)

re		: fclean all

$(OBJDIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY	: all clean fclean re