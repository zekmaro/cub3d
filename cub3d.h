/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 22:09:04 by andrejarama       #+#    #+#             */
/*   Updated: 2024/09/01 16:04:47 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "gnl/get_next_line.h"
# include "libft/libft.h"
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/time.h>
# include <unistd.h>
# include <math.h>
# include "mlx.h"

// KEY DEFINITION LINUX
# define W 119
# define D 100
# define S 115
# define A 97
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_UP 65362
# define KEY_DOWN 65364
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
# define YELLOW 0xFFFF00
# define BEIGE 0xC8AE7E
# define BROWN 0x4C2C17
# define GRAY 0x808080
# define MAGENTA 0xFF00FF
# define LIGHT_BLUE 0x7FDBFF
# define LIGHT_GREEN 0x90EE90

typedef enum e_tex_typ
{
	TEXTURE_NORTH,
	TEXTURE_WEST,
	TEXTURE_SOUTH,
	TEXTURE_EAST
}	t_tex_typ;

typedef struct s_map
{
	char	**grid;
	int		height;
	int		width;
	int		player_x;
	int		player_y;
	char	player_dir;
	int		monster_x;
	int		monster_y;
}	t_map;

typedef struct s_img
{
	void		*mlx_img;
	char		*addr;
	int			bits_per_pixel;
	int			line_len;
	int			endian;
	t_tex_typ	*texture_type;
	int			frame_count;
	int			current_frame;
	void		*current_frame_ptr;
	void		**frames;
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

typedef struct s_ray
{
	double	ray_x;
	double	ray_y;
	double	last_ray_x;
	double	last_ray_y;
	double	ray_dir_x;
	double	ray_dir_y;
	double	ray_angle;
	double	distance_to_wall;
	int		line_height;
	int		draw_start;
	int		draw_end;
}	t_ray;

typedef struct s_player
{
	int		x;
	int		y;
	double	fov;
	int		move_speed;
	int		rot_speed;
	int		player_size;
	int		center_x;
	int		center_y;
	double	angle;
}	t_player;

typedef struct s_vars
{
	int				unit_size;
	t_map			*map;
	t_img			*image;
	t_mlx			*mlx;
	t_line			*line;
	t_player		*player;
	t_ray			*ray;
	t_img			*textures[4];
	t_img			*animated_sprite;
	int				is_monster;
	struct timeval	program_start;
	struct timeval	current_time;
}	t_vars;

// for makefile compilation from linux: -lmlx -lXext -lX11 -lm -o
// for mac: -framework OpenGL -framework AppKit -o

/* Draw_line.c */
void	draw_line(t_vars *vars, unsigned long color);

/* Drawing.c */
void	rotate_around_point(t_vars *vars, int *x, int *y);
void	draw_map(t_vars *vars);

/* Free_memory_utils.c */
void	free_memory(char **arr);
void	free_map(t_map *map);
int		free_and_exit(void *param);
void	free_vars_textures(t_vars *vars);
void	cleanup_vars(t_vars *vars);

/* Free_vars.c */
void	free_vars_map(t_vars *vars);
void	free_vars_image(t_vars *vars);
void	free_vars_player(t_vars *vars);
void	free_vars_mlx(t_vars *vars);
void	free_vars_line(t_vars *vars);
void	free_vars_sprites(t_vars *vars);

/* Handle_image.c */
void	put_pixel_to_image(t_vars *vars, int x, int y, int color);
void	clean_screen(t_vars *vars);
void	get_data_image(t_vars *vars, t_img *image, t_mlx *mlx);

/* Handle_keys.c */
int		mouse_move(int x, int y, t_vars *vars);
int		key_hook(int keycode, t_vars *vars);

/* Inits.c */
void	initialise_vars(t_vars *vars);
void	initialise_textures(t_vars *vars);
void	initialise_sprites(t_vars *vars);

/* Parsing.c */
int		read_map(int fd, t_map *map, char *file_name);

/* Utils.c */
void	print_map(t_map *map);
int		is_wall(t_vars *vars, int y, int x);
int		player_inside_map(t_vars *vars, int x, int y);
int		can_move(t_vars *vars, int y, int x);
int		get_texture_color(t_img *texture, int x, int y);
long	get_elapsed_time(struct timeval *start, struct timeval *end);
void	get_current_time(struct timeval *time);

/* Raycast.c */
void	cast_ray(t_vars *vars, int ray_id);
void	raycast(t_vars *vars);

/* Sprites.c */
void	load_animated_sprite(t_vars *vars, t_img *sprite, \
			const char **file_paths, int frame_count);
void	update_sprite_frame(t_img *sprite);
void	put_enemy_on_screen(t_vars *vars);
int		draw_sprite(t_vars *vars);

#endif // CUB3D_H
