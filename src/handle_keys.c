/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 23:55:11 by andrejarama       #+#    #+#             */
/*   Updated: 2024/09/10 14:17:26 by iberegsz         ###   ########.fr       */
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

int	animate_shooting(t_vars *vars)
{
	static int	frame_count = 0;

	if (!vars->player->shoot)
		return (0);
	get_current_time(&vars->current_time);
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
