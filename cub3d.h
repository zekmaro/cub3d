/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 22:09:04 by andrejarama       #+#    #+#             */
/*   Updated: 2024/09/18 17:17:02 by iberegsz         ###   ########.fr       */
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

# define MINIMAP_RADIUS 100

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
	int		boss_x;
	int		boss_y;
	int		imp_list_size;
	int		caco_list_size;
	int		num_doors;
}	t_map;

typedef struct s_door
{
	int				x;
	int				y;
	int				grid_x;
	int				grid_y;
	int				center_x;
	int				center_y;
	int				offset;
	int				open;
	int				orientation;
	int				state;
	int				distance_to_door;
	double			animation_progress;
	t_img			*textures;
	struct timeval	time0;
	struct timeval	time1;
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

typedef struct s_animation
{
	t_img	*move;
	t_img	*death;
	t_img	*attack;
	t_img	*bullet;
}	t_animation;

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
	int				detected_player;
	int				draw;
	int				shoot_ball;
	t_img			*move;
	t_img			*death;
	t_img			*attack;
	t_img			*current_animation;
	int				current_frame;
	int				fire_ball_x;
	int				fire_ball_y;
	int				fire_delta_x;
	int				fire_delta_y;
	t_img			*fire_ball;
	double			angle;
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
	t_animation		*imp_animation;
	t_enemy			*caco;
	t_enemy			*caco_list;
	t_animation		*caco_animation;
	t_enemy			*boss;
	t_animation		*boss_animation;
	t_ray			*ray;
	t_door			*doors;
	int				minimap_update_x;
	int				minimap_update_y;
	t_img			*textures[8];
	t_img			*animated_sprite;
	int				is_monster;
	struct timeval	program_start;
	struct timeval	current_time;
	int				*zbuffer;
	int				*sprite_order;
	t_sprite		*sprites;
	t_img			*sprite_texture;
	char			*texture_names[4];
	int				num_sprites;
	t_keys			keys;
	int				floor_r;
	int				floor_g;
	int				floor_b;
	int				ceiling_r;
	int				ceiling_g;
	int				ceiling_b;
	int				floor_color;
	int				ceiling_color;
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

typedef struct s_draw_limits
{
	int	draw_start_y;
	int	draw_end_y;
	int	draw_start_x;
	int	draw_end_x;
}	t_draw_limits;

typedef struct s_ray_par
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	angle;
}	t_ray_par;

typedef struct s_player_params
{
	double	dir_y;
	double	dir_x;
	double	plane_y;
	double	plane_x;
}	t_player_params;

typedef struct s_sprite_info
{
	t_img	*sprite;
	int		object_x;
	int		object_y;
	int		scale;
	int		current_frame;
}	t_sprite_info;

typedef struct s_ray_params
{
	int	door_flag;
	int	ray_y;
	int	ray_x;
	int	index;
}	t_ray_params;

// for makefile compilation from linux: -lmlx -lXext -lX11 -lm -o
// for mac: -framework OpenGL -framework AppKit -o

/* Draw_line.c */
void		draw_line(t_vars *vars, unsigned long color);

/* Draw_entities.c */
void		draw_minimap(t_vars *vars);
void		draw_and_update_entity(t_vars *vars, t_enemy *entity, int scale);
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
void		draw_row(t_draw_params *draw_params, t_tex_pos *tex_pos, \
				int screen_y, int scaled_width);
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
void		draw_dynamic_sprite(t_vars *vars, t_sprite_info *sprite_info);

/* Draw_sprite.c */
void		draw_sprites(t_vars *vars);
void		calculate_draw_limits(t_vars *vars, t_sprite *sprite, \
				t_draw_limits *limits);
int			draw_sprite(t_vars *vars);

/* Draw_sprite_stripe.c */
void		draw_sprite_stripe(t_vars *vars, t_sprite_params *params, \
				t_sprite_calc_params *calc_params, t_img *tmp);

/* Draw_environment.c */
void		draw_floor(t_vars *vars);
void		draw_ceiling(t_vars *vars);

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
void		enemy_shoot(t_enemy *enemy, int vector_x, int vector_y, int vector);
void		enemy_act(t_vars *vars, t_enemy *enemy);
void		search_for_player(t_vars *vars);
void		act_detected_enemies(t_vars *vars);
long		update_imp_time(t_vars *vars);

/* Handle_enemy_list.c */
void		init_enemy_lists(t_vars *vars);
void		update_enemy_frames(t_enemy *enemy, long delay);
void		update_enemy_list(t_enemy *enemy_list, long delay, int size);

/* Free_memory_utils.c */
void		free_memory(char **arr);
void		free_vars_zbuffer(t_vars *vars);
int			free_and_exit(t_vars *vars);
void		exit_with_error(t_vars *vars, char *error_message);
void		cleanup_vars(t_vars *vars);

/* Free_environment.c */
void		free_vars_map(t_vars *vars);
void		free_map(t_map *map);
void		free_vars_gun(t_vars *vars);
void		free_frames(t_img **frames, int count);
void		free_doors(t_vars *vars);

/* Free_components.c */
void		free_vars_image(t_vars *vars);
void		free_vars_player(t_vars *vars);
void		free_vars_mlx(t_vars *vars);
void		free_vars_line(t_vars *vars);
void		free_vars_ray(t_vars *vars);

/* Free_sprites.c */
void		free_sprites(t_vars *vars);
void		free_vars_sprites(t_vars *vars);
void		free_sprite_frame(t_img *frame);

/* Free_textures.c */
void		free_textures(t_vars *vars);
void		free_vars_textures(t_vars *vars);
void		free_vars_sprite_texture(t_vars *vars);
void		free_vars_fire(t_vars *vars);
void		free_vars_texture_names(t_vars *vars);

/* Free_enemies.c */
void		free_enemy_list(t_vars *vars);
void		free_enemies(t_vars *vars);
void		free_vars_imp(t_vars *vars);
void		free_vars_caco(t_vars *vars);

/* Free_animations.c */
void		free_animation(t_img **animation, int frame_count);
void		free_imp_animations(t_vars *vars);
void		free_caco_animations(t_vars *vars);
void		free_boss_animations(t_vars *vars);

/* Free_gun_and_fire */
void		free_gun(t_vars *vars);
void		free_fire(t_vars *vars);

/* Free_animation_frames.c */
void		free_animated_frames(t_img **frames, int count);

/* Handle_image.c */
void		put_pixel_to_image(t_vars *vars, int x, int y, int color);
void		clean_screen(t_vars *vars);
void		get_data_image(t_vars *vars, t_img *image, t_mlx *mlx);

/* Handle_keys.c */
int			key_press(int keycode, t_vars *vars);
int			key_up(int keycode, t_vars *vars);
int			animate_shooting(t_vars *vars);

/* Handle_mouse.c */
void		reset_mouse_to_center(t_vars *vars);
int			mouse_move(int x, int y, t_vars *vars);
int			shoot_entity(int button, int x, int y, t_vars *vars);

/* Init_components.c */
void		initialise_line(t_vars *vars);
void		initialise_image(t_vars *vars);
void		initialise_player(t_vars *vars);
void		initialise_ray(t_vars *vars);

/* Init_environment.c */
int			count_frames(const char **frames);
void		initialise_map(t_vars *vars);
void		initialise_zbuffer(t_vars *vars);
void		initialise_doors(t_vars *vars);
void		initialise_vars(t_vars *vars);

/* Init_textures.c*/
void		load_texture(t_vars *vars, int texture_index, \
				const char *file_path);
void		initialise_textures(t_vars *vars);
void		initialise_enemy_textures(t_vars *vars, t_img *animation,
				const char **frames);

/* Init_mlx.c */
void		initialise_mlx(t_vars *vars);
void		safe_init_mlx(t_vars *vars);

/* Init_sprites.c	*/
void		load_sprite_texture(t_vars *vars, t_img *sprite_texture, \
				const char *file_path);
void		allocate_sprite_memory(t_vars *vars, t_img **sprite, \
				const char *error_message);
void		allocate_memory_for_sprites(t_vars *vars);
void		load_sprites(t_vars *vars);
void		initialise_sprites(t_vars *vars);

/* Map_utils.c */
void		print_map(t_map *map);
int			player_inside_map(t_vars *vars, int x, int y);
int			can_move(t_vars *vars, int y, int x);
int			get_texture_color(t_img *texture, int x, int y);

/* Time_utils */
long		get_elapsed_time(struct timeval *start, struct timeval *end);
void		get_current_time(struct timeval *time);

/* Handle_sprites.c */
void		update_sprite_frame(t_img *sprite);
void		calculate_sprite_distances(t_vars *vars);
void		project_sprite(t_vars *vars, t_sprite *sprite);
void		sort_sprites(t_vars *vars);

/* Load_animated_sprite.c */
void		cleanup_sprite_frames(t_vars *vars, t_img **frames, \
				int frame_count);
t_img		*load_sprite_frame(t_vars *vars, const char *file_path, \
				int *width, int *height);
void		load_animated_sprite(t_vars *vars, t_img *sprite, \
				const char **file_paths, int frame_count);

/* Doors */
void		open_door(t_vars *vars, int x, int y);
void		close_door(t_vars *vars, int x, int y);

/* Ray_drawing */
void		get_texture_coords(t_vars *vars, t_tex_typ texture_index, \
				int *tex_x);
t_tex_typ	define_texture_type(t_vars *vars);
int			get_map_x(t_vars *vars);
int			get_map_y(t_vars *vars);

/* Ray_handlers.c */
void		handle_monster(t_vars *vars, int ray_id, int y, int color);
void		handle_door(t_vars *vars, int ray_id, int y, int color);
void		handle_wall(t_vars *vars, int ray_id, int y, int color);
int			get_texture_color_at_y(t_vars *vars, t_tex_typ texture_index, \
				int y, t_tex_coords *coords);

/* Raycasting.c */
void		setup_ray(t_vars *vars, double ray_x, double ray_y);
void		draw_ray_column(t_vars *vars, int ray_id, t_tex_typ texture_index);
void		raycast(t_vars *vars);

/* Is_entity.c */
int			is_player(t_vars *vars, int y, int x);
int			is_enemy(t_enemy *enemy, int y, int x);
int			is_imp(t_vars *vars, int y, int x);
int			is_caco(t_vars *vars, int y, int x);
int			is_monster(t_vars *vars, int x, int y);

/* Is_construction.c */
int			is_wall(t_vars *vars, int y, int x);
int			is_door(t_vars *vars, int y, int x);

/* Gradient.c */
void		draw_player_damaged(t_vars *vars);

/* Init_animations.c */
void		init_imp_sprites(t_vars *vars, t_enemy *imp);
void		init_caco_sprites(t_vars *vars, t_enemy *caco);
void		init_imp_animation(t_vars *vars);
void		init_caco_animation(t_vars *vars);
void		init_cyber_demon_animation(t_vars *vars);

/* Init_enemy.c */
void		init_imp(t_vars *vars, int i, int j, int *counter_imp);
void		init_caco(t_vars *vars, int i, int j, int *counter_caco);
void		init_enemies(t_vars *vars);
void		init_boss(t_vars *vars);

/* Setup_enemies.c */
void		setup_imp(t_vars *vars, t_enemy *imp);
void		setup_caco(t_vars *vars, t_enemy *caco);
void		setup_boss(t_vars *vars, t_enemy *boss);

/* Init_enemy_sprites.c */
void		init_imp_sprite(t_vars *vars, t_animation *imp_animation);
void		init_caco_sprite(t_vars *vars, t_animation *caco_animation);
void		init_boss_sprite(t_vars *vars, t_animation *boss_animation);

/* Init_doors */
void		setup_door(t_vars *vars, t_door *door);
void		init_door(t_vars *vars, int i, int j, int *counter_doors);
void		init_doors(t_vars *vars);
void		printout_doors(t_vars *vars);

/* Handle_door_list.c */
void		update_door_list(t_vars *vars, t_door *door_list, int size);
int			is_closed_door(t_vars *vars, int y, int x);
int			inside_door(t_vars *vars, t_ray_params *params);
int			get_door_id(t_vars *vars, int ray_x, int ray_y);

/* Handle_objects.c */
void		check_objects_to_draw(t_vars *vars);

/* Raycasting_utils.c */
void		get_ray_target_coords(t_vars *vars);

/* Read_map.c */
int			read_map_refactored(int fd, t_map *map, char *file_name);

/* Parsing.c */
int			count_new_lines(int fd, char *line_left);
int			handle_player_direction(char *line, int i, int row, t_map *map);
int			validate_line(char *line, int row, t_map *map);
int			read_map(int fd, t_map *map, char *file_name, char **line_left, \
				int readed_lines);

/* Parse_input.c */
void		parse_color_components(char *line, int *r, int *g, int *b);
void		parse_texture(t_vars *vars, char *line, char **texture);
void		parse_line(t_vars *vars, char *line);

/* Parse_map.c */
int			is_map_surrounded_by_ones(t_map *map);
void		fill_with_ones(t_map *map);
int			parse_file_paths_and_colors(int fd, t_vars *vars, char **line_left);
int			parse_map(int fd, t_map *map);
int			read_map_form_file(int fd, t_map *map, t_vars *vars, \
				char *file_name);

/* Parse_utils.c */
int			check_first_row(char *line);
int			check_last_row(char *line);
int			find_last_zero_index(char *line);

/* Pars_filename.c */
int			has_cub_extension(const char *filename);
int			is_valid_file(const char *filename);
int			is_hidden_file(char *file_name);

#endif // CUB3D_H
