/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 23:55:11 by andrejarama       #+#    #+#             */
/*   Updated: 2024/09/10 13:47:31 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
	if (keycode == SPACE)
		vars->keys.space = 1;
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
	if (keycode == SPACE)
		vars->keys.space = 0;
	if (keycode == KEY_LEFT)
		vars->keys.left = 0;
	if (keycode == KEY_RIGHT)
		vars->keys.right = 0;
	return (0);
}

void	move_player(t_vars *vars, int move_y, int move_x)
{
	int	x;
	int	y;
	int	save_x;
	int	save_y;

	x = vars->player->center_x + move_x * 5;
	y = vars->player->center_y + move_y * 5;
	save_x = x;
	save_y = y;
	rotate_around_point(vars, &x, &y);
	if (can_move(vars, save_y / vars->unit_size, save_x / vars->unit_size))
	{
		vars->player->y += move_y;
		vars->player->x += move_x;
	}
}

void	update_position(t_vars *vars)
{
	int	move_x;
	int	move_y;

	move_x = 8;
	move_y = 8;
	if (vars->keys.w == 1)
		move_player(vars, move_y * sin(vars->player->angle), \
			move_x * cos(vars->player->angle));
	if (vars->keys.s == 1)
		move_player(vars, -move_y * sin(vars->player->angle), \
			-move_x * cos(vars->player->angle));
	if (vars->keys.d == 1)
		move_player(vars, move_y * cos(vars->player->angle), \
			-move_x * sin(vars->player->angle));
	if (vars->keys.a == 1)
		move_player(vars, -move_y * cos(vars->player->angle), \
			move_x * sin(vars->player->angle));
	if (vars->keys.left == 1)
		vars->player->angle -= M_PI / 45;
	if (vars->keys.right == 1)
		vars->player->angle += M_PI / 45;
}

void	check_enemy_collision(t_vars *vars, t_enemy *enemy, int damage)
{
	double	ray_x;
	double	ray_y;
	double	ray_dir_x;
	double	ray_dir_y;
	double	ray_angle;
	int		enemy_flag;

	ray_angle = vars->player->angle;
	ray_x = vars->player->center_x;
	ray_y = vars->player->center_y;
	ray_dir_x = ray_x;
	ray_dir_y = ray_y;
	enemy_flag = 0;
	while (!is_wall(vars, ray_dir_y, ray_dir_x) && !enemy_flag)
	{
		ray_dir_x += cos(ray_angle);
		ray_dir_y += sin(ray_angle);
		enemy_flag = is_enemy(enemy, ray_dir_y, ray_dir_x);
	}
	if (enemy_flag)
	{
		//system("aplay ./assets/imp_pain.wav -q &");
		enemy->health -= damage;
	}
	if (enemy->health == 0)
	{
		// if (!vars->imp->is_dead)
		// 	system("aplay ./assets/imp_death.wav -q &");
		enemy->current_animation = enemy->death_animation;
	}
}

int	animate_shooting(t_vars *vars)
{
	static int	frame_count = 0;
	//long		elapsed_time;

	if (!vars->player->shoot)
		return (0);
	get_current_time(&vars->current_time);
	//elapsed_time = get_elapsed_time(&vars->program_start, &vars->current_time);
	if (frame_count == 2 && !vars->player->fire_done)
	{
		vars->player->fire_done = 1;
		frame_count = 0;
	}
	if (frame_count == 4)
	{
		vars->player->shoot = 0;
		frame_count = 0;
		return (0);
	}
	if (vars->player->fire_done)
		update_sprite_frame(vars->player->gun);
	draw_map(vars);
	if (!vars->player->fire_done)
	{
		draw_fire(vars, 4.0);
		update_sprite_frame(vars->player->fire);
	}
	mlx_put_image_to_window(vars->mlx->mlx, vars->mlx->win, \
		vars->image->mlx_img, 0, 0);
	frame_count++;
	return (0);
}

// void	handle_key(int keycode, t_vars *vars)
// {
// 	int	x;
// 	int	y;

// 	if (keycode == KEY_OPEN_DOOR)
// 	{
// 		x = vars->player->x / vars->unit_size;
// 		y = vars->player->y / vars->unit_size;
// 		//toggle_door(vars, x, y);
// 	}
// 	update_position(vars);
// }

// int	key_hook(int keycode, t_vars *vars)
// {
// 	if (keycode == ESCAPE)
// 		free_and_exit(vars);
// 	else
// 	{
// 		handle_key(keycode, vars);
// 		animate_shooting(vars);
// 	}
// 	return (0);
// }
