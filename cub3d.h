/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 22:09:04 by andrejarama       #+#    #+#             */
/*   Updated: 2024/09/10 14:43:43 by iberegsz         ###   ########.fr       */
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
# define MOUSE_CLICK_LEFT 1
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_UP 65362
# define KEY_DOWN 65364
# define ESCAPE 65307
# define SPACE 32
# define E 101
# define KEY_OPEN_DOOR SPACE

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
# define ORANGE 0xFFA500
# define LIGHT_BLUE 0x7FDBFF
# define LIGHT_GREEN 0x90EE90

# define TRANSPARENT MAGENTA

// DOOR STATES
# define DOOR_CLOSED 0
# define DOOR_OPEN 1
# define DOOR_OPENING 2
# define DOOR_CLOSING 3
# define DOOR_NONE -1

# define MAX_DOORS 10

typedef struct s_pix_inf
{
	int	ray_id;
	int	y;
	int	color;
	int	map_x;
	int	map_y;
}	t_pix_inf;

typedef struct s_tex_coords
{
	int	tex_x;
	int	tex_y;
}	t_tex_coords;

typedef enum e_tex_typ
{
	TEXTURE_NORTH,
	TEXTURE_WEST,
	TEXTURE_SOUTH,
	TEXTURE_EAST,
	TEXTURE_DOOR0,
	TEXTURE_DOOR1,
	TEXTURE_DOOR2,
	TEXTURE_DOOR3,
	TEXTURE_NONE
}	t_tex_typ;

typedef enum e_enemy_type
{
	IMP,
	CACO,
	CYBER_DEMON
}	t_enemy_type;

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
	int			width;
	int			height;
}	t_img;

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
	int		caco_x;
	int		caco_y;
	int		door_x;
	int		door_y;
	int		imp_list_size;
	int		caco_list_size;
	int		num_doors;
}	t_map;

typedef struct s_door
{
	int		center_x;
	int		center_y;
	int		state;
	double	animation_progress;
	t_img	*textures;
}	t_door;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	int		window_width;
	int		window_height;
}	t_mlx;

typedef struct s_line
{
	int		x0;
	int		y0;
	int		x1;
	int		y1;
	int		src_x;
	int		src_y;
	int		dx;
	int		dy;
	int		amount_pixels;
	int		step_x;
	int		step_y;
}	t_line;

typedef struct s_ray
{
	double	ray_x;
	double	ray_y;
	double	last_ray_x;
	double	last_ray_y;
	double	ray_dir_x;
	double	ray_dir_y;
	double	ray_monster_x;
	double	ray_monster_y;
	double	ray_angle;
	double	distance_to_wall;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		hit_door;
	double	door_factor;
}	t_ray;

typedef struct s_player
{
	int				x;
	int				y;
	double			fov;
	int				move_speed;
	int				rot_speed;
	int				player_size;
	int				center_x;
	int				center_y;
	int				health;
	int				is_damaged;
	double			angle;
	double			plane_x;
	double			plane_y;
	double			dir_x;
	double			dir_y;
	int				shoot;
	t_img			*gun;
	t_img			*fire;
	int				fire_done;
	struct timeval	time0;
	struct timeval	time1;
}	t_player;

typedef struct s_sprite
{
	int		x;
	int		y;
	int		distance;
	int		screen_x;
	int		width;
	int		height;
}	t_sprite;

typedef struct s_keys
{
	int		w;
	int		a;
	int		s;
	int		d;
	int		space;
	int		left;
	int		right;
}	t_keys;

typedef struct s_enemy
{
	int				health;
	int				damage;
	int				is_dead;
	int				x;
	int				y;
	int				grid_x;
	int				grid_y;
	int				center_x;
	int				center_y;
	int				rot_dir;
	double			angle;
	int				detected_player;
	t_img			*move_animation;
	t_img			*death_animation;
	t_img			*attack_animation;
	t_img			*fire_ball;
	int				fire_ball_x;
	int				fire_ball_y;
	int				fire_delta_x;
	int				fire_delta_y;
	int				shoot_ball;
	t_img			*current_animation;
	struct timeval	time0;
	struct timeval	time1;
}	t_enemy;

typedef struct s_vars
{
	int				unit_size;
	t_map			*map;
	t_img			*image;
	t_mlx			*mlx;
	t_line			*line;
	t_player		*player;
	t_enemy			*imp;
	t_enemy			*imp_list;
	t_enemy			*caco;
	t_enemy			*caco_list;
	t_ray			*ray;
	t_door			*door;
	t_img			*textures[8];
	t_img			*animated_sprite;
	int				is_monster;
	struct timeval	program_start;
	struct timeval	current_time;
	int				*zbuffer;
	int				*sprite_order;
	t_sprite		*sprites;
	t_img			*sprite_texture;
	int				num_sprites;
	t_img			*door_textures;
	t_keys			keys;
}	t_vars;

typedef struct s_dim
{
	int	width;
	int	height;
}	t_dim;

typedef struct s_scr_pos
{
	int	x;
	int	y;
}	t_scr_pos;

typedef struct s_tex_pos
{
	int	x;
	int	y;
}	t_tex_pos;

typedef struct s_draw_params
{
	t_vars		*vars;
	t_img		*image;
	t_scr_pos	screen_start;
	double		scale;
}	t_draw_params;

typedef struct s_draw_image_params
{
	t_vars	*vars;
	t_img	*image;
	double	scale;
	int		offset_x;
	int		offset_y;
}	t_draw_image_params;

typedef struct s_pixel_params
{
	int		center_x;
	int		center_y;
	double	max_distance;
}	t_pixel_params;

typedef struct s_sprite_params
{
	int	sprite_screen_x;
	int	sprite_height;
	int	sprite_width;
	int	draw_start_y;
	int	draw_end_y;
	int	draw_start_x;
	int	draw_end_x;
}	t_sprite_params;

typedef struct s_sprite_calc_params
{
	double	transform_x;
	double	transform_y;
	int		scale;
}	t_sprite_calc_params;

typedef struct s_draw_sprite_params
{
	t_vars	*vars;
	t_img	*sprite;
	int		object_x;
	int		object_y;
	int		scale;
}	t_draw_sprite_params;

// for makefile compilation from linux: -lmlx -lXext -lX11 -lm -o
// for mac: -framework OpenGL -framework AppKit -o

/* Draw_line.c */
void		draw_line(t_vars *vars, unsigned long color);

/* Draw_entities.c */
void		draw_minimap(t_vars *vars);
void		draw_and_update_entity(t_vars *vars, t_enemy *entity);
void		draw_and_update_entities(t_vars *vars, t_enemy *entity_list, \
				int list_size);
void		draw_map(t_vars *vars);

/* Draw_player.c */
void		draw_player(t_vars *vars, unsigned int color);
void		update_player_position(t_vars *vars);

/* Draw_monster.c */
void		draw_monster(t_vars *vars, unsigned int color);
void		cast_ray_enemy(t_vars *vars, t_enemy *enemy, double angle_offset);
void		search_for_player_enemy(t_vars *vars, t_enemy *enemy);

/* Draw_raycasting.c */
void		draw_ray(t_vars *vars, double angle_offset);
void		draw_ray_segment_player(t_vars *vars);

/* Draw_gunshot.c */
void		draw_scaled_image(t_draw_image_params *params);
void		draw_fire(t_vars *vars, double scale);
void		draw_gun(t_vars *vars, double scale);

/* Draw_gunshot_helper.c */
t_dim		calculate_scaled_dimensions(t_img *image, double scale);
t_dim		calculate_screen_start_position(t_vars *vars, \
				t_dim scaled_dimensions, int offset_x, int offset_y);
void		draw_pixel(t_draw_params *params, t_scr_pos screen_pos, \
				t_tex_pos tex_pos);
t_tex_pos	init_tex_pos(int x, int y);
t_scr_pos	init_scr_pos(int x, int y);

/* Draw_utils.c */
void		draw_square(t_vars *vars, int x, int y, int color);
void		rotate_around_point(t_vars *vars, int *x, int *y);

/* Draw_dynamic_sprite.c */
void		calculate_sprite_params(t_vars *vars, t_sprite_calc_params \
				*calc_params, t_sprite_params *params);
void		calculate_transform(t_draw_sprite_params *draw_params, \
				t_sprite_calc_params *calc_params);
void		draw_sprite_stripe(t_vars *vars, t_sprite_params *params, \
				t_sprite_calc_params *calc_params, t_img *tmp);
void		draw_dynamic_sprite(t_vars *vars, t_img *sprite, int object_x, \
				int object_y, int scale);

/* Draw_environment.c */
void		draw_floor(t_vars *vars);
void		draw_ceiling(t_vars *vars);
void		draw_map(t_vars *vars);
void		draw_minimap(t_vars *vars);

/* Drawing.c */
void		draw_map(t_vars *vars);
void		draw_floor(t_vars *vars);
void		draw_ceiling(t_vars *vars);
void		draw_fire(t_vars *vars, double scale);
void		draw_gun(t_vars *vars, double scale);
void		draw_imp_fire_ball(t_vars *vars);

/* Player_move */
void		move_player(t_vars *vars, int move_y, int move_x);
void		update_position(t_vars *vars);
void		check_enemy_collision(t_vars *vars, t_enemy *enemy, int damage);

/* Handle_player.c */
void		setup_player(t_vars *vars);
int			player_damaged_enemy(t_vars *vars, t_enemy *enemy);
void		update_damaged_player(t_vars *vars);
void		handle_player_damaged_time(t_vars *vars);
void		handle_enemy_shot(t_vars *vars, t_enemy *enemy);

/* Handle_enemies.c */
void		update_enemy_list(t_enemy *enemy_list, long delay, int size);
void		enemy_shoot(t_enemy *enemy, int vector_x, int vector_y, int vector);
void		enemy_act(t_vars *vars, t_enemy *enemy);
void		search_for_player(t_vars *vars);
void		act_detected_enemies(t_vars *vars);

/* Free_memory_utils.c */
void		free_memory(char **arr);
void		free_map(t_map *map);
int			free_and_exit(void *param);
void		free_vars_doors(t_vars *vars);
void		cleanup_vars(t_vars *vars);

/* Free_environment.c */
void		free_vars_map(t_vars *vars);
void		free_vars_textures(t_vars *vars);
void		free_vars_sprites(t_vars *vars);
void		free_vars_line(t_vars *vars);

/* Free_components.c */
void		free_vars_image(t_vars *vars);
void		free_vars_player(t_vars *vars);
void		free_vars_mlx(t_vars *vars);
void		free_vars_ray(t_vars *vars);
void		exit_with_error(t_vars *vars, char *error_message);

/* Free_vars.c */
void		free_vars_map(t_vars *vars);
void		free_vars_image(t_vars *vars);
void		free_vars_player(t_vars *vars);
void		free_vars_mlx(t_vars *vars);
void		free_vars_sprites(t_vars *vars);
void		free_vars_zbuffer(t_vars *vars);

/* Handle_image.c */
void		put_pixel_to_image(t_vars *vars, int x, int y, int color);
void		clean_screen(t_vars *vars);
void		get_data_image(t_vars *vars, t_img *image, t_mlx *mlx);

/* Handle_keys.c */
int			key_press(int keycode, t_vars *vars);
int			key_up(int keycode, t_vars *vars);
int			key_hook(int keycode, t_vars *vars);
int			animate_shooting(t_vars *vars);
void		update_position(t_vars *vars);
void		check_enemy_collision(t_vars *vars, t_enemy *enemy, int damage);

/* Handle_mouse.c */
void		reset_mouse_to_center(t_vars *vars);
int			mouse_move(int x, int y, t_vars *vars);
int			shoot_entity(int button, int x, int y, t_vars *vars);

/* Init_components.c */
void		initialise_mlx(t_vars *vars);
void		initialise_line(t_vars *vars);
void		initialise_image(t_vars *vars);
void		initialise_player(t_vars *vars);
void		initialise_ray(t_vars *vars);

/* Init_environment.c */
void		load_texture(t_vars *vars, int texture_index, \
				const char *file_path);
void		initialise_textures(t_vars *vars);
void		initialise_sprites(t_vars *vars);
void		initialise_map(t_vars *vars);
void		initialise_vars(t_vars *vars);
//void		initialise_doors(t_vars *vars);

/* Init_textures.c*/
void		load_texture(t_vars *vars, int texture_index, \
				const char *file_path);
void		initialise_textures(t_vars *vars);

/* Init_sprites.c	*/
int			count_frames(const char **frames);
void		initialise_enemy_textures(t_vars *vars, t_img *animation,
				const char **frames);
void		load_sprite_texture(t_vars *vars, t_img *sprite_texture, \
				const char *file_path);
void		init_imp_sprites(t_vars *vars, t_enemy *imp);
void		init_caco_sprites(t_vars *vars, t_enemy *caco);
void		initialise_sprites(t_vars *vars);

/* Parsing.c */
int			read_map(int fd, t_map *map, char *file_name);

/* Utils.c */
void		print_map(t_map *map);
int			is_player(t_vars *vars, int y, int x);
int			is_imp(t_vars *vars, int y, int x);
int			is_caco(t_vars *vars, int y, int x);
int			is_wall(t_vars *vars, int y, int x);
int			player_inside_map(t_vars *vars, int x, int y);
int			can_move(t_vars *vars, int y, int x);
int			get_texture_color(t_img *texture, int x, int y);
long		get_elapsed_time(struct timeval *start, struct timeval *end);
void		get_current_time(struct timeval *time);

/* Raycast.c */
void		cast_ray(t_vars *vars, int ray_id);
void		raycast(t_vars *vars);
void		get_texture_coords(t_vars *vars, t_tex_typ texture_index, \
				int *tex_x);
int			is_monster(t_vars *vars, int x, int y);

/* Sprites.c */
void		load_animated_sprite(t_vars *vars, t_img *sprite, \
				const char **file_paths, int frame_count);
void		update_sprite_frame(t_img *sprite);
void		put_enemy_on_screen(t_vars *vars);
int			draw_sprite(t_vars *vars);

/* Doors */
int			is_door(t_vars *vars, int x, int y);
void		open_door(t_vars *vars, int x, int y);
void		close_door(t_vars *vars, int x, int y);
void		toggle_door(t_vars *vars, int x, int y);

/* Ray_handlers.c */
void		handle_monster(t_vars *vars, int ray_id, int y, int color);
void		handle_door(t_vars *vars, int ray_id, int y, int color);
void		handle_wall(t_vars *vars, int ray_id, int y, int color);
void		handle_pixel(t_vars *vars, t_pix_inf *pix_inf);
int			get_texture_color_at_y(t_vars *vars, t_tex_typ texture_index, \
				int y, t_tex_coords *coords);

void		draw_player_damaged(t_vars *vars);
void		draw_door(t_vars *vars);
void		init_imp_sprites(t_vars *vars, t_enemy *imp);
int			is_enemy(t_enemy *enemy, int y, int x);
void		init_caco_sprites(t_vars *vars, t_enemy *caco);
int			functioin(t_vars *vars);

#endif // CUB3D_H
