/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarama <anarama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 22:09:04 by andrejarama       #+#    #+#             */
/*   Updated: 2024/08/29 18:40:46 by anarama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "gnl/get_next_line.h"
# include "libft/libft.h"
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <math.h>
# include "mlx.h"

// KEY DEFINITION LINUX
# define W 119
# define D 100
# define S 115
# define A 97
# define ESCAPE 65307

// KEY DEFINITION MAC
// # define W 13
// # define D 2
// # define S 1
// # define A 0
// # define ESCAPE 53

// COLORS
# define WHITE 0xFFFFFF
# define RED 0xFF0000
# define PURPLE 0x800080
# define BLACK 0x000000
# define BLUE 0x00008B
# define GREEN 0x008000

typedef struct s_map
{
	char	**grid;
	int		height;
	int		width;
	int     player_x;
    int     player_y;
    char    player_dir;
}	t_map;

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bits_per_pixel;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	int		window_width;
	int		window_height;
}	t_mlx;

typedef struct s_line
{
	int	x0;
	int	y0;
	int	x1;
	int	y1;
	int	src_x;
	int	src_y;
	int	dx;
	int	dy;
	int	amount_pixels;
	int	step_x;
	int	step_y;
}	t_line;

typedef struct s_player
{
	int		x;
	int		y;
	int		move_speed;
	int		rot_speed;
	int		player_size;
	int		center_x;
	int		center_y;
	double	angle;
}	t_player;

typedef struct s_vars
{
	int			unit_size;
	t_map		*map;
	t_img		*image;
	t_mlx		*mlx;
	t_line		*line;
	t_player	*player;
}	t_vars;

// for makefile compilation from linux: -lmlx -lXext -lX11 -lm -o
// for mac: -framework OpenGL -framework AppKit -o

/* Draw_line.c */
void	draw_line(t_vars *vars, unsigned long color);

/* Drawing.c */
void	draw_map(t_vars *vars);

/* Free_memory_utils.c */
void	free_memory(char **arr);
void	free_map(t_map *map);
void	free_and_exit(t_vars *vars);
void	cleanup_vars(t_vars *vars);

/* Free_vars.c */
void	free_vars_map(t_vars *vars);
void	free_vars_image(t_vars *vars);
void	free_vars_player(t_vars *vars);
void	free_vars_mlx(t_vars *vars);
void	free_vars_line(t_vars *vars);

/* Handle_iamge.c */
void	put_pixel_to_image(t_vars *vars, int x, int y, int color);
void	clean_screen(t_vars *vars);
void	get_data_image(t_vars *vars, t_img *image, t_mlx *mlx);

/* Handle_keys.c */
int		mouse_move(int x, int y, t_vars *vars);
int		key_hook(int keycode, t_vars *vars);

/* Inits.c */
void	initialise_vars(t_vars *vars);

/* Parsing.c */
int		read_map(int fd, t_map *map, char *file_name);

/* Utils.c */
void	print_map(t_map *map);
int		is_wall(t_vars *vars, int y, int x);
int		player_inside_map(t_vars *vars, int x, int y);
int		can_move(t_vars *vars, int y, int x);

#endif // CUB3D_H