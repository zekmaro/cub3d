/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrejarama <andrejarama@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 22:09:04 by andrejarama       #+#    #+#             */
/*   Updated: 2024/08/22 00:15:20 by andrejarama      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "get_next_line/get_next_line.h"
# include "libft/libft.h"
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <math.h>
# include "minilibx_macos/mlx.h"

// KEY DEFINITION LINUX
// # define W 119
// # define D 100
// # define S 115
// # define A 97
// # define ESCAPE 65307

// KEY DEFINITION MAC
# define W 13
# define D 2
# define S 1
# define A 0
# define ESCAPE 53

// COLORS
# define WHITE 0xFFFFFF
# define RED 0xFF0000
# define PURPLE 0x800080
# define BLACK 0x000000
# define BLUE 0x00008B

typedef struct s_map
{
	char	**grid;
	int		height;
	int		width;
	int     player_x;
    int     player_y;
    char    player_dir;
}	t_map;

typedef struct s_angles
{
	double	angle_x;
	double	angle_y;
	double	angle_z;
}	t_angles;

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bits_per_pixel;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_color
{
	unsigned long	color;
	int				red;
	int				green;
	int				blue;
}	t_color;

typedef struct s_colors
{
	t_color	*low;
	t_color	*top;
}	t_colors;

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
	int	z0;
	int	x1;
	int	y1;
	int	z1;
	int	src_x;
	int	src_y;
	int	dx;
	int	dy;
	int	amount_pixels;
	int	fraction;
	int	step_x;
	int	step_y;
	int	dh;
}	t_line;

typedef struct s_vars
{
	t_map		*map;
	t_img		*image;
	t_img		*color;
	t_colors	*colors;
	t_mlx		*mlx;
	t_line		*line;
}	t_vars;

// for makefile compilation from linux: -lmlx -lXext -lX11 -lm -o
// for mac: -framework OpenGL -framework AppKit -o

int		read_map(int fd, t_map *map, char *file_name);
void	initialise_vars(t_vars *vars);
void	print_map(t_map *map);

int		key_hook(int keycode, t_vars *vars);
void	clean_screen(t_vars *vars);
void	get_data_image(t_vars *vars, t_img *image, t_mlx *mlx);
void	put_pixel_to_image(t_vars *vars, int x, int y, int color);

#endif // CUB3D_H