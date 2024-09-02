/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iberegsz <iberegsz@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 23:55:11 by andrejarama       #+#    #+#             */
/*   Updated: 2024/09/02 13:08:10 by iberegsz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	move_player(t_vars *vars, int move_y, int move_x)
{
	int	x;
	int	y;
	int	save_x;
	int	save_y;

	x = vars->player->center_x + move_x;
	y = vars->player->center_y + move_y;
	save_x = x;
	save_y = y;
	rotate_around_point(vars, &x, &y);
	if (can_move(vars, save_y / vars->unit_size, save_x / vars->unit_size))
	{
		vars->player->y += move_y;
		vars->player->x += move_x;
	}
}

int	mouse_move(int x, int y, t_vars *vars)
{
	(void)y;
	vars->player->angle = (x / 360);
	draw_map(vars);
	mlx_put_image_to_window(vars->mlx->mlx, vars->mlx->win,
		vars->image->mlx_img, 0, 0);
	return (0);
}

void	check_move_player(int keycode, t_vars *vars)
{
	int	move_x;
	int	move_y;

	move_x = 8;
	move_y = 8;
	if (keycode == W)
		move_player(vars, move_y * sin(vars->player->angle), \
			move_x * cos(vars->player->angle));
	else if (keycode == S)
		move_player(vars, -move_y * sin(vars->player->angle), \
			-move_x * cos(vars->player->angle));
	else if (keycode == D)
		move_player(vars, move_y * cos(vars->player->angle), \
			-move_x * sin(vars->player->angle));
	else if (keycode == A)
		move_player(vars, -move_y * cos(vars->player->angle), \
			move_x * sin(vars->player->angle));
	else if (keycode == KEY_LEFT)
		vars->player->angle -= M_PI / 6;
	else if (keycode == KEY_RIGHT)
		vars->player->angle += M_PI / 6;
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
	check_move_player(keycode, vars);
}

int	key_hook(int keycode, t_vars *vars)
{
	if (keycode == ESCAPE)
		free_and_exit(vars);
	else
	{
		clean_screen(vars);
		handle_key(keycode, vars);
		draw_map(vars);
		mlx_put_image_to_window(vars->mlx->mlx, vars->mlx->win,
			vars->image->mlx_img, 0, 0);
		put_enemy_on_screen(vars);
	}
	return (0);
}
