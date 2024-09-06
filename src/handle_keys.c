/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 23:55:11 by andrejarama       #+#    #+#             */
/*   Updated: 2024/09/06 12:50:00 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	reset_mouse_to_center(t_vars *vars)
{
	int center_x;
	int center_y;

	center_x = vars->mlx->window_width / 2;
	center_y = vars->mlx->window_height / 2;
    mlx_mouse_move(vars->mlx->mlx, vars->mlx->win, center_x, center_y);
}

int	mouse_move(int x, int y, t_vars *vars)
{
	int center_x = vars->mlx->window_width / 2;
	(void)y;
   // int center_y = vars->mlx->window_height / 2;
 
	int dx = x - center_x;
    //int dy = y - center_y;
	// double magnitude;

	// magnitude = sqrt(x * x + y * y);
	// dx /= magnitude;
    // Update player angle based on mouse movement (dx affects rotation)
	double rot_speed = 0.002; // Adjust this for desired sensitivity
	
	vars->player->angle += dx * rot_speed;
	// printf("mouse moved: %d %f\n", dx, vars->player->angle);
	reset_mouse_to_center(vars);
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
	if (can_move(vars, save_y / vars->unit_size , save_x / vars->unit_size))
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
	else if (vars->keys.s == 1)
		move_player(vars, -move_y * sin(vars->player->angle), \
			move_x * cos(vars->player->angle));
	else if (vars->keys.d == 1)
		move_player(vars, move_y * cos(vars->player->angle), \
			move_x * sin(vars->player->angle));
	else if (vars->keys.a == 1)
		move_player(vars, -move_y * cos(vars->player->angle), \
			move_x * sin(vars->player->angle));
	else if (vars->keys.left == 1)
		vars->player->angle -= M_PI / 90;
	else if (vars->keys.right == 1)
		vars->player->angle += M_PI / 90;
}

int	animate_shooting(t_vars *vars)
{
	static int frame_count = 0;

	if (!vars->player->shoot)
		return (0);
	long elapsed_time;
	get_current_time(&vars->current_time);
	elapsed_time = get_elapsed_time(&vars->program_start, &vars->current_time);
	// if (elapsed_time % 10 == 0)
	// {
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
	mlx_put_image_to_window(vars->mlx->mlx, vars->mlx->win, vars->image->mlx_img, 0, 0);
	frame_count++;
	// }
	return (0);
}

int	shoot_this_shit(int button, int x, int y, t_vars *vars)
{
	(void)x;
	(void)y;

	if (button == MOUSE_CLICK_LEFT && !vars->player->shoot)
	{
		system("aplay ./assets/gunshot.wav -q &");
		vars->player->shoot = 1;
		vars->player->fire_done = 0;
	}
	return (0);
}

void	handle_key(int keycode, t_vars *vars)
{
	int	x;
	int	y;

	if (keycode == KEY_OPEN_DOOR)
	{
		x = vars->player->x / vars->unit_size;
		y = vars->player->y / vars->unit_size;
		toggle_door(vars, x, y);
	}
	update_position(vars);
}

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
