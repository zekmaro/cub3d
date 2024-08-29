/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarama <anarama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 23:55:11 by andrejarama       #+#    #+#             */
/*   Updated: 2024/08/29 23:06:33 by anarama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	move_player(t_vars *vars, int move_y, int move_x)
{
	int x;
	int y;

	x = (vars->player->center_x + move_x);
	y = (vars->player->center_y + move_y);
	rotate_around_point(&x, &y, vars->player->center_x, vars->player->center_y, vars->player->angle);
	if (can_move(vars, y / vars->unit_size, x / vars->unit_size))
	{
		vars->player->y = y;
		vars->player->x = x;	
	}
}

int mouse_move(int x, int y, t_vars *vars)
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
	if (keycode == W)
	{
		move_player(vars, -vars->player->player_size, 0);
	}
	else if (keycode == S)
	{
		move_player(vars, vars->player->player_size, 0);
	}
	else if (keycode == D)
	{
		move_player(vars, 0, vars->player->player_size);
	}
	else if (keycode == A)
	{
		move_player(vars, 0, -vars->player->player_size);
	}
	else if (keycode == KEY_LEFT)
		vars->player->angle -= M_PI / 6;
	else if (keycode == KEY_RIGHT)
		vars->player->angle += M_PI / 6;
		
}

void	handle_key(int keycode, t_vars *vars)
{
	check_move_player(keycode, vars);
}

int	key_hook(int keycode, t_vars *vars)
{
	if (keycode == ESCAPE)
	{
		free_and_exit(vars);
	}
	else
	{
		clean_screen(vars);
		handle_key(keycode, vars);
		draw_map(vars);
		mlx_put_image_to_window(vars->mlx->mlx, vars->mlx->win,
			vars->image->mlx_img, 0, 0);
	}
	return (0);
}
