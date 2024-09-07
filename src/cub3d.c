/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarama <anarama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 22:04:39 by andrejarama       #+#    #+#             */
/*   Updated: 2024/09/07 23:29:24 by anarama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <math.h>
#include <stdio.h>

long	update_imp_time(t_vars *vars)
{
	long	elapsed_time;

	get_current_time(&vars->imp->time1);
	elapsed_time = get_elapsed_time(&vars->imp->time0, &vars->imp->time1);
	return (elapsed_time);
}


int	key_press(int keycode, t_vars *vars)
{
	if (keycode == ESCAPE)
		free_and_exit(vars);
	if (keycode == W)
		vars->keys.w = 1;
	if (keycode == S)
		vars->keys.s = 1;
	if (keycode == A)
		vars->keys.a = 1;
	if (keycode == D)
		vars->keys.d = 1;
	if (keycode == KEY_LEFT)
		vars->keys.left = 1;
	if (keycode == KEY_RIGHT)
		vars->keys.right = 1;
	return (0);
}

int	key_up(int keycode, t_vars *vars)
{
	if (keycode == ESCAPE)
		free_and_exit(vars);
	if (keycode == W)
		vars->keys.w = 0;
	if (keycode == S)
		vars->keys.s = 0;
	if (keycode == A)
		vars->keys.a = 0;
	if (keycode == D)
		vars->keys.d = 0;
	if (keycode == KEY_LEFT)
		vars->keys.left = 0;
	if (keycode == KEY_RIGHT)
		vars->keys.right = 0;
	return (0);
}

int	player_damaged(t_vars *vars)
{
	return (abs(vars->imp->fire_ball_x - vars->player->center_x) < 20
		&& abs(vars->imp->fire_ball_y - vars->player->center_y) < 20
		&& !vars->player->is_damaged);
}

int	main_loop_hook(t_vars *vars)
{
	struct timeval t;
	double abc;

	get_current_time(&t);
	get_current_time(&vars->imp->time1);
	get_current_time(&vars->player->time1);
	abc = (double)t.tv_sec + (double)t.tv_usec / 1000000;
	long imp_elapsed_time = get_elapsed_time(&vars->imp->time0, &vars->imp->time1);
	if (imp_elapsed_time > 200)
	{
		if (vars->imp->current_animation == vars->imp->death_animation
			&& vars->imp->current_animation->current_frame == vars->imp->current_animation->frame_count - 1)
		{
			vars->imp->is_dead = 1;
			vars->imp->center_x = -100;
			vars->imp->center_y = -100;
		}
		update_sprite_frame(vars->imp->current_animation);
		if (vars->imp->current_animation == vars->imp->attack_animation
		&& vars->imp->current_animation->current_frame == vars->imp->current_animation->frame_count - 1)
			vars->imp->current_animation = vars->imp->move_animation;
		vars->imp->time0 = vars->imp->time1;
	long time_player_damaged = get_elapsed_time(&vars->player->time0, &vars->player->time1);
	if (time_player_damaged > 500)
	{
		vars->player->is_damaged = 0;
	}
	}
	update_position(vars);
	draw_sprite(vars);
	if (vars->player->shoot)
		animate_shooting(vars);
	if (!vars->imp->detected_player)
		vars->imp->angle += M_PI / 10 * vars->imp->rot_dir;
	if (vars->imp->detected_player)
	{
		int vector_x = vars->player->center_x - vars->imp->center_x;
		int vector_y = vars->player->center_y - vars->imp->center_y;
		int vector = sqrt(vector_x * vector_x + vector_y * vector_y);
		if (!vars->imp->shoot_ball)
		{
			if (vars->imp->health > 0)
				vars->imp->current_animation = vars->imp->attack_animation;
			vars->imp->fire_delta_y = (vector_y * vector_y / vector) / 10;
			if (vector_y < 0)
				vars->imp->fire_delta_y *= -1;
			vars->imp->fire_delta_x = (vector_x * vector_x / vector) / 10;
			if (vector_x < 0)
				vars->imp->fire_delta_x *= -1;
			vars->imp->shoot_ball = 1;
		}
		vars->imp->center_x += vector_x / 40;
		vars->imp->center_y += vector_y / 40;
		if (is_wall(vars, vars->imp->fire_ball_y, vars->imp->fire_ball_x))
		{
			vars->imp->fire_ball_y = vars->imp->center_y;
			vars->imp->fire_ball_x = vars->imp->center_x;
			vars->imp->shoot_ball = 0;
		}
		else
		{
			if (player_damaged(vars))
			{
				printf("hello\n");
				vars->player->is_damaged = 1;
				vars->player->health -= 20;
				get_current_time(&vars->player->time0);
				system("aplay ./assets/player_pain.wav -q &");
				if (vars->player->health == 0)
				{
					printf("GAME OVER!\n");
					system("aplay ./assets/player_dead.wav -q &");
					free_and_exit(vars);
				}
				vars->imp->fire_ball_y = 0;
				vars->imp->fire_ball_x = 0;
			}
			else
			{
				vars->imp->fire_ball_y += vars->imp->fire_delta_y;
				vars->imp->fire_ball_x += vars->imp->fire_delta_x;		
			}
		}
		vars->imp->detected_player = 0;
	}
	if (vars->player->is_damaged)
	{
		draw_player_damaged(vars);
	}
	get_current_time(&t);
	printf("diff: %1.12f\n", ((double)t.tv_sec + (double)t.tv_usec / 1000000) - abc);
	return (0);
}

void	run_screen(t_vars *vars)
{
	vars->mlx->mlx = mlx_init();
	vars->mlx->win = mlx_new_window(vars->mlx->mlx, vars->mlx->window_width, \
		vars->mlx->window_height, "Gestalt Cube3D");
	get_data_image(vars, vars->image, vars->mlx);
	initialise_textures(vars);
	initialise_sprites(vars);
	draw_door(vars);
	draw_map(vars);
	mlx_put_image_to_window(vars->mlx->mlx, vars->mlx->win,
		vars->image->mlx_img, 0, 0);
	reset_mouse_to_center(vars);
	mlx_hook(vars->mlx->win, 2, 1L << 0, key_press, vars);
	mlx_hook(vars->mlx->win, 3, 1L << 1, key_up, vars);
	mlx_mouse_hook(vars->mlx->win, shoot_this_shit, vars);
	mlx_hook(vars->mlx->win, 6, 1L << 6, mouse_move, vars);
	mlx_loop_hook(vars->mlx->mlx, main_loop_hook, vars);
	mlx_hook(vars->mlx->win, 17, 0, free_and_exit, vars);
	mlx_loop(vars->mlx->mlx);
}
//mlx_hook(vars->mlx->win, 6, 1L << 6, mouse_move, vars);
// mlx_key_hook(vars->mlx->win, key_hook, vars);

int	game_loop(t_vars *vars)
{
	draw_map(vars);
	mlx_put_image_to_window(vars->mlx->mlx, vars->mlx->win,
		vars->image->mlx_img, 0, 0);
	return (0);
}

void	setup_player(t_vars *vars)
{
	double	plane_length;

	vars->player->x = (vars->map->player_x * vars->unit_size) \
		+ vars->unit_size / 2;
	vars->player->y = (vars->map->player_y * vars->unit_size) \
		+ vars->unit_size / 2;
	vars->player->fov = M_PI / 3;
	if (vars->map->player_dir == 'N')
		vars->player->angle = -M_PI / 2;
	else if (vars->map->player_dir == 'W')
		vars->player->angle = -M_PI;
	else if (vars->map->player_dir == 'S')
		vars->player->angle = -3 * M_PI / 2;
	else if (vars->map->player_dir == 'E')
		vars->player->angle = 0;
	vars->player->dir_x = cos(vars->player->angle);
	vars->player->dir_y = sin(vars->player->angle);
	plane_length = tan(vars->player->fov / 2);
	vars->player->plane_x = -vars->player->dir_y * plane_length;
	vars->player->plane_y = vars->player->dir_x * plane_length;
	vars->player->health = 100;
}

void	setup_imp(t_vars *vars)
{
	vars->imp->x = (vars->map->monster_x * vars->unit_size);
	vars->imp->y = (vars->map->monster_y * vars->unit_size);
	vars->imp->center_x = vars->imp->x + vars->unit_size / 2;
	vars->imp->center_y = vars->imp->y + vars->unit_size / 2;
	vars->imp->angle = -M_PI / 2;
	vars->imp->rot_dir = 1;
	vars->imp->fire_ball_x = vars->imp->center_x;
	vars->imp->fire_ball_y = vars->imp->center_y;
}

void	setup_door(t_vars *vars)
{
	vars->door->center_x = vars->map->door_x * vars->unit_size + vars->unit_size / 2;
	vars->door->center_y = vars->map->door_y * vars->unit_size + vars->unit_size / 2;
	printf("door center x: %d\n", vars->door->center_x);
	printf("door center y: %d\n", vars->door->center_y);
}

int	main(int argc, char **argv)
{
	t_vars	vars;
	int		fd;

	if (argc != 2)
	{
		perror("Usage: ./cub3D [path]<filename>.cub\n");
		exit(EXIT_FAILURE);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		perror("Invalid file descriptor!\n");
		exit(EXIT_FAILURE);
	}
	ft_bzero(&vars, sizeof(t_vars));
	initialise_vars(&vars);
	if (!read_map(fd, vars.map, argv[1]))
		free_and_exit(&vars);
	setup_player(&vars);
	setup_imp(&vars);
	setup_door(&vars);
	get_current_time(&vars.program_start);
	get_current_time(&vars.imp->time0);
	//print_map(vars.map);
	run_screen(&vars);
	return (0);
}

// get_current_time(&vars.program_start);
//print_map(vars.map);
// run_screen(&vars);